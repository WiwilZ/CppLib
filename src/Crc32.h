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
#include <immintrin.h>
#   endif


uint32_t Crc32_AVX512(const void* data, size_t length, uint32_t crc = 0) noexcept {
    const auto* buffer = static_cast<const __m512i*>(data);

    // There's at least one block of 256
    __m512i x1 = _mm512_loadu_si512(buffer + 0);
    __m512i x2 = _mm512_loadu_si512(buffer + 1);
    __m512i x3 = _mm512_loadu_si512(buffer + 2);
    __m512i x4 = _mm512_loadu_si512(buffer + 3);

    buffer += 4;
    length -= 256;

    x1 = _mm512_xor_si512(x1, _mm512_castsi128_si512(_mm_cvtsi32_si128(crc)));

    __m512i x0 = _mm512_set_epi64(0x01322d1430, 0x011542778a, 0x01322d1430, 0x011542778a, 0x01322d1430, 0x011542778a, 0x01322d1430, 0x011542778a);

    __m512i x5, x6, x7, x8, y5, y6, y7, y8;

    // Parallel fold blocks of 256
    while (length >= 256) {
        x5 = _mm512_clmulepi64_epi128(x1, x0, 0x00);
        x6 = _mm512_clmulepi64_epi128(x2, x0, 0x00);
        x7 = _mm512_clmulepi64_epi128(x3, x0, 0x00);
        x8 = _mm512_clmulepi64_epi128(x4, x0, 0x00);

        x1 = _mm512_clmulepi64_epi128(x1, x0, 0x11);
        x2 = _mm512_clmulepi64_epi128(x2, x0, 0x11);
        x3 = _mm512_clmulepi64_epi128(x3, x0, 0x11);
        x4 = _mm512_clmulepi64_epi128(x4, x0, 0x11);

        y5 = _mm512_loadu_si512(buffer + 0);
        y6 = _mm512_loadu_si512(buffer + 1);
        y7 = _mm512_loadu_si512(buffer + 2);
        y8 = _mm512_loadu_si512(buffer + 3);

        x1 = _mm512_xor_si512(x1, x5);
        x2 = _mm512_xor_si512(x2, x6);
        x3 = _mm512_xor_si512(x3, x7);
        x4 = _mm512_xor_si512(x4, x8);

        x1 = _mm512_xor_si512(x1, y5);
        x2 = _mm512_xor_si512(x2, y6);
        x3 = _mm512_xor_si512(x3, y7);
        x4 = _mm512_xor_si512(x4, y8);

        buffer += 4;
        length -= 256;
    }

    // Fold into 512-bits
    x0 = _mm512_set_epi64(0x01c6e41596, 0x0154442bd4, 0x01c6e41596, 0x0154442bd4, 0x01c6e41596, 0x0154442bd4, 0x01c6e41596, 0x0154442bd4);

    x5 = _mm512_clmulepi64_epi128(x1, x0, 0x00);
    x1 = _mm512_clmulepi64_epi128(x1, x0, 0x11);
    x1 = _mm512_xor_si512(x1, x2);
    x1 = _mm512_xor_si512(x1, x5);

    x5 = _mm512_clmulepi64_epi128(x1, x0, 0x00);
    x1 = _mm512_clmulepi64_epi128(x1, x0, 0x11);
    x1 = _mm512_xor_si512(x1, x3);
    x1 = _mm512_xor_si512(x1, x5);

    x5 = _mm512_clmulepi64_epi128(x1, x0, 0x00);
    x1 = _mm512_clmulepi64_epi128(x1, x0, 0x11);
    x1 = _mm512_xor_si512(x1, x4);
    x1 = _mm512_xor_si512(x1, x5);

    // Single fold blocks of 64
    while (length >= 64) {
        x2 = _mm512_loadu_si512(buffer);

        x5 = _mm512_clmulepi64_epi128(x1, x0, 0x00);
        x1 = _mm512_clmulepi64_epi128(x1, x0, 0x11);
        x1 = _mm512_xor_si512(x1, x2);
        x1 = _mm512_xor_si512(x1, x5);

        ++buffer;
        length -= 64;
    }

    // Fold 512-bits to 384-bits
    __m128i a0 = _mm_set_epi64x(0x00000000ccaa009e, 0x00000001751997d0);

    __m128i a1 = _mm512_extracti32x4_epi32(x1, 0);
    __m128i a2 = _mm512_extracti32x4_epi32(x1, 1);

    __m128i a3 = _mm_clmulepi64_si128(a1, a0, 0x00);
    a1 = _mm_clmulepi64_si128(a1, a0, 0x11);

    a1 = _mm_xor_si128(a1, a3);
    a1 = _mm_xor_si128(a1, a2);

    // Fold 384-bits to 256-bits
    a2 = _mm512_extracti32x4_epi32(x1, 2);
    a3 = _mm_clmulepi64_si128(a1, a0, 0x00);
    a1 = _mm_clmulepi64_si128(a1, a0, 0x11);
    a1 = _mm_xor_si128(a1, a3);
    a1 = _mm_xor_si128(a1, a2);

    // Fold 256-bits to 128-bits
    a2 = _mm512_extracti32x4_epi32(x1, 3);
    a3 = _mm_clmulepi64_si128(a1, a0, 0x00);
    a1 = _mm_clmulepi64_si128(a1, a0, 0x11);
    a1 = _mm_xor_si128(a1, a3);
    a1 = _mm_xor_si128(a1, a2);

    // Fold 128-bits to 64-bits
    a2 = _mm_clmulepi64_si128(a1, a0, 0x10);
    a3 = _mm_setr_epi32(~0, 0, ~0, 0);
    a1 = _mm_srli_si128(a1, 8);
    a1 = _mm_xor_si128(a1, a2);

    a0 = _mm_set_epi64x(0, 0x0163cd6124);
    a2 = _mm_srli_si128(a1, 4);
    a1 = _mm_and_si128(a1, a3);
    a1 = _mm_clmulepi64_si128(a1, a0, 0x00);
    a1 = _mm_xor_si128(a1, a2);

    // Barret reduce to 32-bits
    a0 = _mm_set_epi64x(0x01f7011641, 0x01db710641);

    a2 = _mm_and_si128(a1, a3);
    a2 = _mm_clmulepi64_si128(a2, a0, 0x10);
    a2 = _mm_and_si128(a2, a3);
    a2 = _mm_clmulepi64_si128(a2, a0, 0x00);
    a1 = _mm_xor_si128(a1, a2);

    return _mm_extract_epi32(a1, 1);
}

#elif defined(__SSE4_2__) && defined(__PCLMUL__)

#   if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>
#   else
#include <smmintrin.h>
#include <wmmintrin.h>
#   endif


uint32_t Crc32_SSE4(const void* data, size_t length, uint32_t crc = 0) noexcept {
    const auto* buffer = static_cast<const __m128i*>(data);

    // There's at least one block of 64
    __m128i x1 = _mm_loadu_si128(buffer + 0);
    __m128i x2 = _mm_loadu_si128(buffer + 1);
    __m128i x3 = _mm_loadu_si128(buffer + 2);
    __m128i x4 = _mm_loadu_si128(buffer + 3);

    buffer += 4;
    length -= 64;

    x1 = _mm_xor_si128(x1, _mm_cvtsi32_si128(crc));

    __m128i x0 = _mm_set_epi64x(0x00000001c6e41596, 0x0000000154442bd4);

    __m128i x5, x6, x7, x8, y5, y6, y7, y8;

    // Parallel fold blocks of 64
    while (length >= 64) {
        x5 = _mm_clmulepi64_si128(x1, x0, 0x00);
        x6 = _mm_clmulepi64_si128(x2, x0, 0x00);
        x7 = _mm_clmulepi64_si128(x3, x0, 0x00);
        x8 = _mm_clmulepi64_si128(x4, x0, 0x00);

        x1 = _mm_clmulepi64_si128(x1, x0, 0x11);
        x2 = _mm_clmulepi64_si128(x2, x0, 0x11);
        x3 = _mm_clmulepi64_si128(x3, x0, 0x11);
        x4 = _mm_clmulepi64_si128(x4, x0, 0x11);

        y5 = _mm_loadu_si128(buffer + 0);
        y6 = _mm_loadu_si128(buffer + 1);
        y7 = _mm_loadu_si128(buffer + 2);
        y8 = _mm_loadu_si128(buffer + 3);

        x1 = _mm_xor_si128(x1, x5);
        x2 = _mm_xor_si128(x2, x6);
        x3 = _mm_xor_si128(x3, x7);
        x4 = _mm_xor_si128(x4, x8);

        x1 = _mm_xor_si128(x1, y5);
        x2 = _mm_xor_si128(x2, y6);
        x3 = _mm_xor_si128(x3, y7);
        x4 = _mm_xor_si128(x4, y8);

        buffer += 4;
        length -= 64;
    }

    // Fold into 128-bits
    x0 = _mm_set_epi64x(0x00000000ccaa009e, 0x00000001751997d0);

    x5 = _mm_clmulepi64_si128(x1, x0, 0x00);
    x1 = _mm_clmulepi64_si128(x1, x0, 0x11);
    x1 = _mm_xor_si128(x1, x2);
    x1 = _mm_xor_si128(x1, x5);

    x5 = _mm_clmulepi64_si128(x1, x0, 0x00);
    x1 = _mm_clmulepi64_si128(x1, x0, 0x11);
    x1 = _mm_xor_si128(x1, x3);
    x1 = _mm_xor_si128(x1, x5);

    x5 = _mm_clmulepi64_si128(x1, x0, 0x00);
    x1 = _mm_clmulepi64_si128(x1, x0, 0x11);
    x1 = _mm_xor_si128(x1, x4);
    x1 = _mm_xor_si128(x1, x5);

    // Single fold blocks of 16
    while (length >= 16) {
        x2 = _mm_loadu_si128(buffer);

        x5 = _mm_clmulepi64_si128(x1, x0, 0x00);
        x1 = _mm_clmulepi64_si128(x1, x0, 0x11);
        x1 = _mm_xor_si128(x1, x2);
        x1 = _mm_xor_si128(x1, x5);

        ++buffer;
        length -= 16;
    }

    // Fold 128-bits to 64-bits
    x2 = _mm_clmulepi64_si128(x1, x0, 0x10);
    x3 = _mm_setr_epi32(~0, 0, ~0, 0);
    x1 = _mm_srli_si128(x1, 8);
    x1 = _mm_xor_si128(x1, x2);

    x0 = _mm_set_epi64x(0x0000000000000000, 0x0000000163cd6124);

    x2 = _mm_srli_si128(x1, 4);
    x1 = _mm_and_si128(x1, x3);
    x1 = _mm_clmulepi64_si128(x1, x0, 0x00);
    x1 = _mm_xor_si128(x1, x2);

    // Barret reduce to 32-bits
    x0 = _mm_set_epi64x(0x00000001f7011641, 0x00000001db710641);

    x2 = _mm_and_si128(x1, x3);
    x2 = _mm_clmulepi64_si128(x2, x0, 0x10);
    x2 = _mm_and_si128(x2, x3);
    x2 = _mm_clmulepi64_si128(x2, x0, 0x00);
    x1 = _mm_xor_si128(x1, x2);

    return _mm_extract_epi32(x1, 1);
}

#endif


#include <array>


namespace Detail {
    constexpr auto Crc32Table = [] {
        constexpr uint32_t Polynomial = 0xEDB88320;
        constexpr size_t N = 8;
        std::array<std::array<uint32_t, 256>, N> table{};
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t crc = i;
            for (uint32_t j = 0; j < 8; j++) {
                crc = (crc >> 1) ^ (-(crc & 1) & Polynomial);
            }
            table[0][i] = crc;
        }
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t crc = table[0][i];
            for (uint32_t j = 1; j < N; j++) {
                crc = (crc >> 8) ^ table[0][crc & 0xFF];
                table[j][i] = crc;
            }
        }
        return table;
    }();
}


uint32_t Crc32(const void* data, size_t length, uint32_t crc = 0) noexcept {
    const auto* buffer = static_cast<const uint8_t*>(data);

    crc = ~crc;

#ifdef __AVX512F__
    const size_t chunkSize = length & ~63;
    crc = Crc32_AVX512(data, chunkSize, crc);
    length &= 63;
    if (length == 0) {
        return ~crc;
    }
    buffer += chunkSize;
#elif defined(__SSE4_2__) && defined(__PCLMUL__)
    const size_t chunkSize = length & ~15;
    crc = Crc32_SSE4(data, chunkSize, crc);
    length &= 15;
    if (length == 0) {
        return ~crc;
    }
    buffer += chunkSize;
#endif

    while (length >= 8) {
        const uint64_t x = *reinterpret_cast<const uint64_t*>(buffer) ^ crc;
        crc = Detail::Crc32Table[0][x >> 56] ^ Detail::Crc32Table[1][(x >> 48) & 0xFF] ^
              Detail::Crc32Table[2][(x >> 40) & 0xFF] ^ Detail::Crc32Table[3][(x >> 32) & 0xFF] ^
              Detail::Crc32Table[4][(x >> 24) & 0xFF] ^ Detail::Crc32Table[5][(x >> 16) & 0xFF] ^
              Detail::Crc32Table[6][(x >> 8) & 0xFF] ^ Detail::Crc32Table[7][x & 0xFF];
        buffer += 8;
        length -= 8;
    }
    if (length & 4) {
        crc ^= *reinterpret_cast<const uint32_t*>(buffer);
        crc = Detail::Crc32Table[0][crc >> 24] ^ Detail::Crc32Table[1][(crc >> 16) & 0xFF] ^
              Detail::Crc32Table[2][(crc >> 8) & 0xFF] ^ Detail::Crc32Table[3][crc & 0xFF];
        buffer += 4;
    }
    if (length & 2) {
        crc ^= *reinterpret_cast<const uint16_t*>(buffer);
        crc = Detail::Crc32Table[0][crc >> 8] ^ Detail::Crc32Table[1][crc & 0xFF];
        buffer += 2;
    }
    if (length & 1) {
        crc ^= *buffer;
        crc = (crc >> 8) ^ Detail::Crc32Table[0][crc & 0xFF];
    }
    return ~crc;
}
