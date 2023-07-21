//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concepts/Integral.h"
#include "../Traits/MakeIntegerType.h"
#include "../ArithmeticType.h"
#include "../Macro.h"


#if defined(_MSC_VER) && !defined(__clang__)
extern "C" {
    unsigned long _byteswap_ulong(unsigned long);
    unsigned __int64 _byteswap_uint64(unsigned __int64);
}
#elif HAS_INT128 && defined(__SSSE3__)
#include <emmintrin.h>
#include <tmmintrin.h>
#endif



namespace detail {
    namespace common {
        static constexpr u8 BitReverseTable[256] {
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

        [[nodiscard]] constexpr u8 BitReverse(u8 x) noexcept {
            // This method is slower than the table lookup
            // x = (x << 4) | (x >> 4);
            // x = ((x & 0x33) << 2) | ((x >> 2) & 0x33);
            // x = ((x & 0x55) << 1) | ((x >> 1) & 0x55);
            // return x;
            return BitReverseTable[x];
        }

        [[nodiscard]] constexpr u16 BitReverse(u16 x) noexcept {
            // This method is slower than the table lookup
            // x = (x << 8) | (x >> 8);
            // x = ((x & 0x0F0F) << 4) | ((x >> 4) & 0x0F0F);
            // x = ((x & 0x3333) << 2) | ((x >> 2) & 0x3333);
            // x = ((x & 0x5555) << 1) | ((x >> 1) & 0x5555);
            // return x;
            return (BitReverseTable[x & 0xFF] << 8) | BitReverseTable[x >> 8];
        }

        [[nodiscard]] constexpr u32 BitReverse(u32 x) noexcept {
            x = (x << 16) | (x >> 16);
            x = ((x & 0x00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF);
            x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);
            x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
            x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
            return x;
        }

        [[nodiscard]] constexpr u64 BitReverse(u64 x) noexcept {
            x = (x << 32) | (x >> 32);
            x = ((x & 0x0000FFFF0000FFFF) << 16) | ((x >> 16) & 0x0000FFFF0000FFFF);
            x = ((x & 0x00FF00FF00FF00FF) << 8) | ((x >> 8) & 0x00FF00FF00FF00FF);
            x = ((x & 0x0F0F0F0F0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F0F0F0F0F);
            x = ((x & 0x3333333333333333) << 2) | ((x >> 2) & 0x3333333333333333);
            x = ((x & 0x5555555555555555) << 1) | ((x >> 1) & 0x5555555555555555);
            return x;
        }

#if HAS_INT128
        [[nodiscard]] constexpr u128 BitReverse(u128 x) noexcept {
            constexpr u128 C0 = (u128{0x00000000FFFFFFFF} << 64) | 0x00000000FFFFFFFF;
            constexpr u128 C1 = (u128{0x0000FFFF0000FFFF} << 64) | 0x0000FFFF0000FFFF;
            constexpr u128 C2 = (u128{0x00FF00FF00FF00FF} << 64) | 0x00FF00FF00FF00FF;
            constexpr u128 C3 = (u128{0x0F0F0F0F0F0F0F0F} << 64) | 0x0F0F0F0F0F0F0F0F;
            constexpr u128 C4 = (u128{0x3333333333333333} << 64) | 0x3333333333333333;
            constexpr u128 C5 = (u128{0x5555555555555555} << 64) | 0x5555555555555555;
            x = (x << 64) | (x >> 64);
            x = ((x & C0) << 32) | ((x >> 32) & C0);
            x = ((x & C1) << 16) | ((x >> 16) & C1);
            x = ((x & C2) << 8) | ((x >> 8) & C2);
            x = ((x & C3) << 4) | ((x >> 4) & C3);
            x = ((x & C4) << 2) | ((x >> 2) & C4);
            x = ((x & C5) << 1) | ((x >> 1) & C5);
            return x;
        }
#endif
    } // namespace common



    [[nodiscard]] constexpr u32 BitReverseAfterByteSwap(u32 x) noexcept {
        x = ((x & 0x0f0f0f0f) << 4) | ((x >> 4) & 0x0f0f0f0f);
        x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
        x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
        return x;
    }

    [[nodiscard]] constexpr u64 BitReverseAfterByteSwap(u64 x) noexcept {
        x = ((x & 0x0f0f0f0f0f0f0f0f) << 4) | ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
        x = ((x & 0x3333333333333333) << 2) | ((x >> 2) & 0x3333333333333333);
        x = ((x & 0x5555555555555555) << 1) | ((x >> 1) & 0x5555555555555555);
        return x;
    }

#if HAS_INT128
    [[nodiscard]] constexpr u128 BitReverseAfterByteSwap(u128 x) noexcept {
        constexpr u128 C0 = (u128{0x0f0f0f0f0f0f0f0f} << 64) | 0x0f0f0f0f0f0f0f0f;
        constexpr u128 C1 = (u128{0x3333333333333333} << 64) | 0x3333333333333333;
        constexpr u128 C2 = (u128{0x5555555555555555} << 64) | 0x5555555555555555;
        x = ((x & C0) << 4) | ((x >> 4) & C0);
        x = ((x & C1) << 2) | ((x >> 2) & C1);
        x = ((x & C2) << 1) | ((x >> 1) & C2);
        return x;
    }
#endif



    [[nodiscard]] constexpr u8 BitReverse(u8 x) noexcept {
        return common::BitReverse(x);
    }

    [[nodiscard]] constexpr u16 BitReverse(u16 x) noexcept {
        return common::BitReverse(x);
    }

    [[nodiscard]] constexpr u32 BitReverse(u32 x) noexcept {
#if HAS_BUILTIN(__builtin_bitreverse32)
        return __builtin_bitreverse32(x);
#elif HAS_BUILTIN(__builtin_bswap32)
        return BitReverseAfterByteSwap(static_cast<u32>(__builtin_bswap32(x)));
#else // !HAS_BUILTIN(__builtin_bitreverse32) && !HAS_BUILTIN(__builtin_bswap32)
#   if defined(_MSC_VER) && !defined(__clang__)
        if (!__builtin_is_constant_evaluated()) {
            return BitReverseAfterByteSwap(static_cast<u32>(_byteswap_ulong(x)));
        }
#   endif
        return common::BitReverse(x);
#endif
    }

    [[nodiscard]] constexpr u64 BitReverse(u64 x) noexcept {
#if HAS_BUILTIN(__builtin_bitreverse64)
        return __builtin_bitreverse64(x);
#elif HAS_BUILTIN(__builtin_bswap64)
        return BitReverseAfterByteSwap(static_cast<u64>(__builtin_bswap64(x)));
#else // !HAS_BUILTIN(__builtin_bitreverse64) && !HAS_BUILTIN(__builtin_bswap64)
#   if defined(_MSC_VER) && !defined(__clang__)
        if (!__builtin_is_constant_evaluated()) {
            return BitReverseAfterByteSwap(static_cast<u64>(_byteswap_uint64(x)));
        }
#   endif
        return common::BitReverse(x);
#endif
    }

#if defined(__SIZEOF_INT128__)
    [[nodiscard]] constexpr u128 BitReverse(u128 x) noexcept {
#   if HAS_BUILTIN(__builtin_bitreverse64)
        return (u128{__builtin_bitreverse64(x)} << 64) | __builtin_bitreverse64(x >> 64);
#   elif HAS_BUILTIN(__builtin_bswap128)
        return BitReverseAfterByteSwap(__builtin_bswap128(x));
#   elif HAS_BUILTIN(__builtin_bswap64)
        return BitReverseAfterByteSwap((u128{__builtin_bswap64(x)} << 64) | __builtin_bswap64(x >> 64));
#   else // !HAS_BUILTIN(__builtin_bitreverse64) && !HAS_BUILTIN(__builtin_bswap128) && !HAS_BUILTIN(__builtin_bswap64)
#       ifdef __SSSE3__
        if (!__builtin_is_constant_evaluated()) {
            const __m128i r = __builtin_bit_cast(__m128i, x);
            const __m128i c0 = _mm_set1_epi8(0x0f);
            const __m128i c1 = _mm_setr_epi8(0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0);
            const __m128i c2 = _mm_setr_epi8(0x00, 0x08, 0x04, 0x0c, 0x02, 0x0a, 0x06, 0x0e, 0x01, 0x09, 0x05, 0x0d, 0x03, 0x0b, 0x07, 0x0f);
            const __m128i low = _mm_shuffle_epi8(c1, _mm_and_si128(c0, r));
            const __m128i high = _mm_shuffle_epi8(c2, _mm_srli_epi32(_mm_andnot_si128(c0, r), 4));
            return __builtin_bit_cast(u128, _mm_or_si128(low, high));
        }
#       endif
        return common::BitReverse(x);
#   endif
    }
#endif // __SIZEOF_INT128__
} // namespace detail



template <concepts::Integral T>
[[nodiscard]] constexpr T BitReverse(T x) noexcept {
    return detail::BitReverse(static_cast<traits::MakeUInt_T<sizeof(T)>>(x));
}

