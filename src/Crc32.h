//
// Created by WiwilZ on 2023/6/19.
//

#pragma once

#include <cstdint>
#include <cstddef>

#ifdef __AVX512F__

#   if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>
#   else
#include <emmintrin.h>
#include <smmintrin.h>
#include <wmmintrin.h>
#include <immintrin.h>
#   endif


uint32_t Crc32(const void* buf, std::size_t len, uint32_t crc = 0) noexcept {
    static constexpr alignas(64) uint64_t k1k2[]{
            0x011542778a, 0x01322d1430,
            0x011542778a, 0x01322d1430,
            0x011542778a, 0x01322d1430,
            0x011542778a, 0x01322d1430
    };
    static constexpr alignas(64) uint64_t k3k4[]{
            0x0154442bd4, 0x01c6e41596,
            0x0154442bd4, 0x01c6e41596,
            0x0154442bd4, 0x01c6e41596,
            0x0154442bd4, 0x01c6e41596
    };
    static constexpr alignas(16) uint64_t k5k6[]{ 0x01751997d0, 0x00ccaa009e };
    static constexpr uint64_t k7 = 0x0163cd6124;
    static constexpr alignas(16) uint64_t poly[]{ 0x01db710641, 0x01f7011641 };

    const __m512i* p = buf;
    const __m512i* q = reinterpret_cast<const __m512i*>(static_cast<const uint8_t*>(buf) + len);

    // There's at least x0 block of 256.
    __m512i x0 = _mm512_load_si512(k1k2);
    __m512i x1 = _mm512_xor_si512(_mm512_castsi128_si512(_mm_cvtsi32_si128(crc)), _mm512_loadu_si512(p++));
    __m512i x2 = _mm512_loadu_si512(p++);
    __m512i x3 = _mm512_loadu_si512(p++);
    __m512i x4 = _mm512_loadu_si512(p++);

    // Parallel fold blocks of 256, if any.
    while (p + 4 <= q) {
        x1 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x1, x0, 0x11), _mm512_clmulepi64_epi128(x1, x0, 0x00)), _mm512_loadu_si512(p++));
        x2 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x2, x0, 0x11), _mm512_clmulepi64_epi128(x2, x0, 0x00)), _mm512_loadu_si512(p++));
        x3 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x3, x0, 0x11), _mm512_clmulepi64_epi128(x3, x0, 0x00)), _mm512_loadu_si512(p++));
        x4 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x4, x0, 0x11), _mm512_clmulepi64_epi128(x4, x0, 0x00)), _mm512_loadu_si512(p++));
    }

    // Fold into 512-bits.
    x0 = _mm512_load_si512(k3k4);
    x1 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x1, x0, 0x11), x2), _mm512_clmulepi64_epi128(x1, x0, 0x00));
    x1 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x1, x0, 0x11), x3), _mm512_clmulepi64_epi128(x1, x0, 0x00));
    x1 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x1, x0, 0x11), x4), _mm512_clmulepi64_epi128(x1, x0, 0x00));

    // Single fold blocks of 64, if any.
    while (p + 1 <= q) {
        x2 = _mm512_loadu_si512(p++);
        x1 = _mm512_xor_si512(_mm512_xor_si512(_mm512_clmulepi64_epi128(x1, x0, 0x11), x2), _mm512_clmulepi64_epi128(x1, x0, 0x00));
    }

    // Fold 512-bits to 384-bits.
    __m128i a0 = _mm_load_si128(reinterpret_cast<const __m128i*>(k5k6));
    __m128i a1 = _mm512_extracti32x4_epi32(x1, 0);
    __m128i a2 = _mm512_extracti32x4_epi32(x1, 1);
    __m128i a3 = _mm_clmulepi64_si128(a1, a0, 0x00);

    a1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(a1, a0, 0x11), a3), a2);

    // Fold 384-bits to 256-bits.
    a2 = _mm512_extracti32x4_epi32(x1, 2);
    a3 = _mm_clmulepi64_si128(a1, a0, 0x00);
    a1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(a1, a0, 0x11), a3), a2);

    // Fold 256-bits to 128-bits.
    a2 = _mm512_extracti32x4_epi32(x1, 3);
    a3 = _mm_clmulepi64_si128(a1, a0, 0x00);
    a1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(a1, a0, 0x11), a3), a2);

    // Fold 128-bits to 64-bits.
    a2 = _mm_clmulepi64_si128(a1, a0, 0x10);
    a1 = _mm_xor_si128(_mm_srli_si128(a1, 8), a2);

    a3 = _mm_setr_epi32(~0, 0, ~0, 0);
    a0 = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(k7));

    a2 = _mm_srli_si128(a1, 4);
    a1 = _mm_xor_si128(_mm_clmulepi64_si128(_mm_and_si128(a1, a3), a0, 0x00), a2);

    // Barret reduce to 32-bits.
    a0 = _mm_load_si128(reinterpret_cast<const __m128i*>(poly));
    a2 = _mm_clmulepi64_si128(_mm_and_si128(_mm_clmulepi64_si128(_mm_and_si128(a1, a3), a0, 0x10), a3), a0, 0x00);
    a1 = _mm_xor_si128(a1, a2);

    // Return the crc32.
    return _mm_extract_epi32(a1, 1);
}

#elif defined(__SSE4_2__)

#   if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>
#   else
#include <emmintrin.h>
#include <smmintrin.h>
#include <wmmintrin.h>
#   endif


uint32_t Crc32(const void* buf, std::size_t len, uint32_t crc = 0) noexcept {
    static constexpr alignas(16) uint64_t k1k2[]{ 0x0154442bd4, 0x01c6e41596 };
    static constexpr alignas(16) uint64_t k3k4[]{ 0x01751997d0, 0x00ccaa009e };
    static constexpr uint64_t k5 = 0x0163cd6124;
    static constexpr alignas(16) uint64_t poly[]{ 0x01db710641, 0x01f7011641 };

    const __m128i* p = buf;
    const __m128i* q = reinterpret_cast<const __m128i*>(static_cast<const uint8_t*>(buf) + len);

    // There's at least x0 block of 64.
    __m128i x0 = _mm_load_si128(reinterpret_cast<const __m128i*>(k1k2));
    __m128i x1 = _mm_xor_si128(_mm_loadu_si128(p++), _mm_cvtsi32_si128(crc));
    __m128i x2 = _mm_loadu_si128(p++);
    __m128i x3 = _mm_loadu_si128(p++);
    __m128i x4 = _mm_loadu_si128(p++);

    // Parallel fold blocks of 64, if any.
    while (p + 4 <= q) {
        x1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x1, x0, 0x11), _mm_clmulepi64_si128(x1, x0, 0x00)), _mm_loadu_si128(p++));
        x2 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x2, x0, 0x11), _mm_clmulepi64_si128(x2, x0, 0x00)), _mm_loadu_si128(p++));
        x3 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x3, x0, 0x11), _mm_clmulepi64_si128(x3, x0, 0x00)), _mm_loadu_si128(p++));
        x4 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x4, x0, 0x11), _mm_clmulepi64_si128(x4, x0, 0x00)), _mm_loadu_si128(p++));
    }

    // Fold into 128-bits.
    x0 = _mm_load_si128(reinterpret_cast<const __m128i*>(k3k4));
    x1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x1, x0, 0x11), x2), _mm_clmulepi64_si128(x1, x0, 0x00));
    x1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x1, x0, 0x11), x3), _mm_clmulepi64_si128(x1, x0, 0x00));
    x1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x1, x0, 0x11), x4), _mm_clmulepi64_si128(x1, x0, 0x00));

    // Single fold blocks of 16, if any.
    while (p + 1 <= q) {
        x2 = _mm_loadu_si128(p++);
        x1 = _mm_xor_si128(_mm_xor_si128(_mm_clmulepi64_si128(x1, x0, 0x11), x2), _mm_clmulepi64_si128(x1, x0, 0x00));
    }

    // Fold 128-bits to 64-bits.
    x2 = _mm_clmulepi64_si128(x1, x0, 0x10);
    x1 = _mm_xor_si128(_mm_srli_si128(x1, 8), x2);

    x3 = _mm_setr_epi32(~0, 0, ~0, 0);
    x0 = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(k5));

    x2 = _mm_srli_si128(x1, 4);
    x1 = _mm_xor_si128(_mm_clmulepi64_si128(_mm_and_si128(x1, x3), x0, 0x00), x2);

    // Barret reduce to 32-bits.
    x0 = _mm_load_si128(reinterpret_cast<const __m128i*>(poly));
    x2 = _mm_clmulepi64_si128(_mm_and_si128(_mm_clmulepi64_si128(_mm_and_si128(x1, x3), x0, 0x10), x3), x0, 0x00);
    x1 = _mm_xor_si128(x1, x2);

    // Return the crc32.
    return _mm_extract_epi32(x1, 1);
}

#else // !defined(__AVX512F__) && !defined(__SSE4_2__)

#include <array>


namespace Detail {
    constexpr auto Crc32Table = [] {
        constexpr uint32_t Polynomial = 0xEDB88320;
        std::array<std::array<uint32_t, 256>, 8> table{};
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t crc = i;
            for (uint32_t j = 0; j < 8; j++) {
                crc = (crc >> 1) ^ (-(crc & 1) & Polynomial);
            }
            table[0][i] = crc;
        }
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t crc = table[0][i];
            for (uint32_t j = 1; j < 8; j++) {
                crc = (crc >> 8) ^ table[0][crc & 0xFF];
                table[j][i] = crc;
            }
        }
        return table;
    }();
}


uint32_t Crc32(const void* buf, std::size_t len, uint32_t crc = 0) noexcept {
    const uint8_t* p = static_cast<const uint8_t*>(buf);

    crc = ~crc;
    for (; len >= 8; len -= 8) {
        uint64_t x = *reinterpret_cast<const uint64_t*>(p) ^ crc;
        crc = Detail::Crc32Table[0][x >> 56] ^ Detail::Crc32Table[1][(x >> 48) & 0xFF] ^ Detail::Crc32Table[2][(x >> 40) & 0xFF] ^ Detail::Crc32Table[3][(x >> 32) & 0xFF] ^
                Detail::Crc32Table[4][(x >> 24) & 0xFF]  ^ Detail::Crc32Table[5][(x >> 16) & 0xFF] ^ Detail::Crc32Table[6][(x >> 8) & 0xFF] ^ Detail::Crc32Table[7][x & 0xFF];
        p += 8;
    }
    if (len & 4) {
        crc ^= *reinterpret_cast<const uint32_t*>(p);
        crc = Detail::Crc32Table[0][crc >> 24] ^ Detail::Crc32Table[1][(crc >> 16) & 0xFF] ^ Detail::Crc32Table[2][(crc >> 8) & 0xFF] ^ Detail::Crc32Table[3][crc & 0xFF];
        p += 4;
    }
    if (len & 2) {
        crc ^= *reinterpret_cast<const uint16_t*>(p);
        crc = Detail::Crc32Table[0][crc >> 8] ^ Detail::Crc32Table[1][crc & 0xFF];
        p += 2;
    }
    if (len & 1) {
        crc ^= *p;
        crc = (crc >> 8) ^ Detail::Crc32Table[0][crc & 0xFF];
    }
    return ~crc;
}

#endif