//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>

#if defined(_MSC_VER) && !defined(__clang__)

extern "C" {
    unsigned short _byteswap_ushort(unsigned short);
    unsigned long _byteswap_ulong(unsigned long);
    unsigned __int64 _byteswap_uint64(unsigned __int64);
}

#elif (__has_builtin(__builtin_bswap128) || __has_builtin(__builtin_bswap64)) && defined(__SSE2__) && defined(__SSSE3__)

#include <tmmintrin.h>

#endif



namespace Detail {

    static constexpr uint8_t BitReverseTable[256]{
            0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
            0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
            0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
            0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
            0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
            0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
            0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
            0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
            0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
            0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
            0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
            0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
            0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
            0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
            0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
            0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
    };


    namespace BSwap {

        [[nodiscard]] constexpr uint32_t BitReverse(uint32_t x) noexcept {
            x = ((x & 0x0f0f0f0f) << 4) | ((x >> 4) & 0x0f0f0f0f);
            x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
            x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
            return x;
        }

        [[nodiscard]] constexpr uint64_t BitReverse(uint64_t x) noexcept {
            x = ((x & 0x0f0f0f0f0f0f0f0f) << 4) | ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
            x = ((x & 0x3333333333333333) << 2) | ((x >> 2) & 0x3333333333333333);
            x = ((x & 0x5555555555555555) << 1) | ((x >> 1) & 0x5555555555555555);
            return x;
        }

#ifdef __SIZEOF_INT128__

        [[nodiscard]] constexpr __uint128_t BitReverse(__uint128_t x) noexcept {
            constexpr __uint128_t c0 = (__uint128_t{0x0f0f0f0f0f0f0f0f} << 64) | 0x0f0f0f0f0f0f0f0f;
            constexpr __uint128_t c1 = (__uint128_t{0x3333333333333333} << 64) | 0x3333333333333333;
            constexpr __uint128_t c2 = (__uint128_t{0x5555555555555555} << 64) | 0x5555555555555555;
            x = ((x & c0) << 4) | ((x >> 4) & c0);
            x = ((x & c1) << 2) | ((x >> 2) & c1);
            x = ((x & c2) << 1) | ((x >> 1) & c2);
            return x;
        }

#endif

    } // namespace BSwap


    namespace Common {
        [[nodiscard]] constexpr uint32_t BitReverse(uint32_t x) noexcept {
            return (BitReverseTable[x & 0xFF] << 24) | (BitReverseTable[(x >> 8) & 0xFF] << 16) |
                   (BitReverseTable[(x >> 16) & 0xFF] << 8) | BitReverseTable[x >> 24];
        }

        [[nodiscard]] constexpr uint64_t BitReverse(uint64_t x) noexcept {
            return (static_cast<uint64_t>(BitReverseTable[x & 0xFF]) << 56) |
                   (static_cast<uint64_t>(BitReverseTable[(x >> 8) & 0xFF]) << 48) |
                   (static_cast<uint64_t>(BitReverseTable[(x >> 16) & 0xFF]) << 40) |
                   (static_cast<uint64_t>(BitReverseTable[(x >> 24) & 0xFF]) << 32) |
                   (static_cast<uint64_t>(BitReverseTable[(x >> 32) & 0xFF]) << 24) |
                   (static_cast<uint64_t>(BitReverseTable[(x >> 40) & 0xFF]) << 16) |
                   (static_cast<uint64_t>(BitReverseTable[(x >> 48) & 0xFF]) << 8) |
                   static_cast<uint64_t>(BitReverseTable[x >> 56]);
        }

#ifdef __SIZEOF_INT128__

        [[nodiscard]] constexpr __uint128_t BitReverse(__uint128_t x) noexcept {
            return (static_cast<__uint128_t>(BitReverse(static_cast<uint64_t>(x))) << 64) | BitReverse(static_cast<uint64_t>(x >> 64));
        }

#endif

    } // namespace Common



    [[nodiscard]] constexpr uint8_t BitReverse(uint8_t x) noexcept {
        return BitReverseTable[x];
    }

    [[nodiscard]] constexpr uint16_t BitReverse(uint16_t x) noexcept {
        return (BitReverseTable[x & 0xFF] << 8) | BitReverseTable[x >> 8];
    }

    [[nodiscard]] constexpr uint32_t BitReverse(uint32_t x) noexcept {
#if __has_builtin(__builtin_bitreverse32)
        return __builtin_bitreverse32(x);
#elif __has_builtin(__builtin_bswap32)
        return BSwap::BitReverse(__builtin_bswap32(x));
#else // !__has_builtin(__builtin_bitreverse32) && !__has_builtin(__builtin_bswap32)
#   if defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return BSwap::BitReverse(static_cast<uint32_t>(_byteswap_ulong(x)));
        }
#   endif
        return Common::BitReverse(x);
#endif
    }

    [[nodiscard]] constexpr uint64_t BitReverse(uint64_t x) noexcept {
#if __has_builtin(__builtin_bitreverse64)
        return __builtin_bitreverse64(x);
#elif __has_builtin(__builtin_bswap64)
        return BSwap::BitReverse(__builtin_bswap64(x));
#else // !__has_builtin(__builtin_bitreverse64) && !__has_builtin(__builtin_bswap64)
#   if defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return BSwap::BitReverse(_byteswap_uint64(x));
        }
#   endif
        return Common::BitReverse(x);
#endif
    }

#ifdef __SIZEOF_INT128__

    [[nodiscard]] constexpr __uint128_t BitReverse(__uint128_t x) noexcept {
#   if __has_builtin(__builtin_bitreverse64)
        return (static_cast<__uint128_t>(__builtin_bitreverse64(x)) << 64) | __builtin_bitreverse64(x >> 64);
#   elif (__has_builtin(__builtin_bswap128) || __has_builtin(__builtin_bswap64))
#       if __has_builtin(__builtin_bswap128)
        x = __builtin_bswap128(x);
#       else // !__has_builtin(__builtin_bswap128)
        x = (static_cast<__uint128_t>(__builtin_bswap64(x)) << 64) | __builtin_bswap64(x >> 64);
#       endif // __has_builtin(__builtin_bswap128)

#       if defined(__SSE2__) && defined(__SSSE3__)
        if (!__builtin_is_constant_evaluated()) {
            __m128i r = *reinterpret_cast<__m128i*>(&x);
            static const __m128i c0 = _mm_set1_epi8(0x0f);
            static const __m128i c1 = _mm_setr_epi8(0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0);
            static const __m128i c2 = _mm_setr_epi8(0x00, 0x08, 0x04, 0x0c, 0x02, 0x0a, 0x06, 0x0e, 0x01, 0x09, 0x05, 0x0d, 0x03, 0x0b, 0x07, 0x0f);
            __m128i low = _mm_shuffle_epi8(c1, _mm_and_si128(c0, r));
            __m128i high = _mm_shuffle_epi8(c2, _mm_srli_epi32(_mm_andnot_si128(c0, r), 4));
            r = _mm_or_si128(low, high);
            _mm_store_si128(reinterpret_cast<__m128i*>(&x), r);
            return x;
        }
#       endif // defined(__SSE2__) && defined(__SSSE3__)

        return BSwap::BitReverse(x);
#   else // !__has_builtin(__builtin_bitreverse64) && !(__has_builtin(__builtin_bswap128) || __has_builtin(__builtin_bswap64))
        return Common::BitReverse(x);
#   endif
    }

#endif

} // namespace Detail



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T BitReverse(T x) noexcept {
        return Detail::BitReverse(static_cast<Trait::MakeUnsigned_T<T>>(x));
    }

} // namespace Bit
