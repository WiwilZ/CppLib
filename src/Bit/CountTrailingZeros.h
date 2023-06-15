//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../Concept/Integer.h"

#include <cstdint>
#include <climits>


#if defined(__GNUC__) || defined(__clang__)

namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountTrailingZeros(T x) noexcept {
        if constexpr (sizeof(T) <= 4) {
            if (x == 0) {
                return sizeof(T) * CHAR_BIT;
            }
            return __builtin_ctz(x);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_ctzll(x);
        } else {
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            const uint64_t low = x;
            if (low != 0) {
                return __builtin_ctzll(low);
            }
            const uint64_t high = static_cast<__uint128_t>(x) >> 64;
            return __builtin_ctzll(high) + 64;
        }
    }

} // namespace Bit

#else // !defined(__GNUC__) && !defined(__clang__)

namespace Detail::Common {

    static constexpr uint8_t TrailingZerosTable[256]{
        8, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
        4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
    };


    /*  Build de Bruijn Sequence
     *  def deBruijn(n):
            a = [0] * (n + 1)
            alphabet = [0, 1]
            d = 0

            def db(t, p):
                nonlocal d
                if t > n:
                    if n % p == 0:
                        for i in a[1:p + 1]:
                            d = (d << 1) | alphabet[i]
                else:
                    a[t] = a[t - p]
                    db(t + 1, p)
                    for j in range(a[t - p] + 1, 2):
                        a[t] = j
                        db(t + 1, t)
            db(1, 1)

            bits = 1 << n
            mask = (1 << bits) - 1
            shift = bits - n
            seq = [0] * bits
            for i in range(bits):
                seq[((d << i) & mask) >> shift] = i

            return d, seq
     * */

    template <typename T>
    struct CountTrailingZerosImpl;

    template <>
    struct CountTrailingZerosImpl<uint16_t> {
        using Type = uint16_t;
        static constexpr uint16_t deBruijn = 0x9af;
        static constexpr uint8_t deBruijnTable[16]{
            0, 1, 2, 5, 3, 9, 6, 11,
            15, 4, 8, 10, 14, 7, 13, 12
        };
        static constexpr int Shift = 16 - 4;
    };

    template <>
    struct CountTrailingZerosImpl<uint32_t> {
        using Type = uint32_t;
        static constexpr uint32_t deBruijn = 0x4653adf;
        static constexpr uint8_t deBruijnTable[32]{
            0, 1, 2, 6, 3, 11, 7, 16,
            4, 14, 12, 21, 8, 23, 17, 26,
            31, 5, 10, 15, 13, 20, 22, 25,
            30, 9, 19, 24, 29, 18, 28, 27
        };
        static constexpr int Shift = 32 - 5;
    };

    template <>
    struct CountTrailingZerosImpl<uint64_t> {
        using Type = uint64_t;
        static constexpr uint64_t deBruijn = 0x218a392cd3d5dbf;
        static constexpr uint8_t deBruijnTable[64]{
            0, 1, 2, 7, 3, 13, 8, 19,
            4, 25, 14, 28, 9, 34, 20, 40,
            5, 17, 26, 38, 15, 46, 29, 48,
            10, 31, 35, 54, 21, 50, 41, 57,
            63, 6, 12, 18, 24, 27, 33, 39,
            16, 37, 45, 47, 30, 53, 49, 56,
            62, 11, 23, 32, 36, 44, 52, 55,
            61, 22, 43, 51, 60, 42, 59, 58
        };
        static constexpr int Shift = 64 - 6;
    };

#ifdef __SIZEOF_INT128__

    template <>
    struct CountTrailingZerosImpl<__uint128_t> {
        using Type = __uint128_t;
        static constexpr __uint128_t deBruijn = __uint128_t{0x106143891634793} << 64 | 0x2a5cd9d3ead7b77f;
        static constexpr uint8_t deBruijnTable[128]{
                0, 1, 2, 8, 3, 15, 9, 22,
                4, 29, 16, 36, 10, 43, 23, 50,
                5, 33, 30, 57, 17, 64, 37, 71,
                11, 60, 44, 78, 24, 85, 51, 92,
                6, 20, 34, 48, 31, 69, 58, 90,
                18, 67, 65, 99, 38, 101, 72, 106,
                12, 40, 61, 82, 45, 103, 79, 113,
                25, 74, 86, 116, 52, 108, 93, 120,
                127, 7, 14, 21, 28, 35, 42, 49,
                32, 56, 63, 70, 59, 77, 84, 91,
                19, 47, 68, 89, 66, 98, 100, 105,
                39, 81, 102, 112, 73, 115, 107, 119,
                126, 13, 27, 41, 55, 62, 76, 83,
                46, 88, 97, 104, 80, 111, 114, 118,
                125, 26, 54, 75, 87, 96, 110, 117,
                124, 53, 95, 109, 123, 94, 122, 121
        };
        static constexpr int Shift = 128 - 7;
    };

#endif // __SIZEOF_INT128__


    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountTrailingZeros(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return TrailingZerosTable[static_cast<uint8_t>(x)];
        } else {
            if (x == 0) {
                return sizeof(T) * CHAR_BIT;
            }
            using Impl = CountTrailingZerosImpl<T>;
            return Impl::deBruijnTable[static_cast<Impl::Type>(x & -x) * Impl::deBruijn >> Impl::Shift];
        }
    }

} // namespace Detail::Common


#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) && !defined(__INTEL_COMPILER)

#ifndef __AVX2__

#include <isa_availability.h>
extern "C" {
    extern int __isa_available;

    unsigned char _BitScanForward(unsigned long*, unsigned long);
    unsigned char _BitScanForward64(unsigned long*, unsigned __int64);
}


namespace Detail::X86_64::BSF {

    template <Concept::Integer T>
    [[nodiscard]] __forceinline int CountTrailingZeros(T x) noexcept {
        unsigned long result;
        if constexpr (sizeof(T) <= 4) {
            if (_BitScanForward(&result, x)) {
                return result;
            }
        } else {
            static_assert(sizeof(T) == 8, "Unexpected integer size");
#ifdef _M_IX86
            const uint32_t low = x;
            if (_BitScanForward(&result, low)) {
                return result;
            }
            const uint32_t high = static_cast<uint64_t>(x) >> 32;
            if (_BitScanForward(&result, high)) {
                return result + 32;
            }
#else // !defined(_M_IX86)
            if (_BitScanForward64(&result, x)) {
                return result;
            }
#endif
        }
        return sizeof(T) * CHAR_BIT;
    }

} // namespace Detail::X86_64::BSF

#endif // !defined(__AVX2__)

extern "C" {
    unsigned int _tzcnt_u32(unsigned int);
    unsigned __int64 _tzcnt_u64(unsigned __int64);
}


namespace Detail::X86_X64 {

    namespace TZCNT {

        template <Concept::Integer T>
        [[nodiscard]] __forceinline int CountTrailingZeros(T x) noexcept {
            if constexpr (sizeof(T) <= 4) {
                if (x == 0) {
                    return sizeof(T) * CHAR_BIT;
                }
                return _tzcnt_u32(x);
            } else {
                static_assert(sizeof(T) == 8, "Unexpected integer size");
#   ifdef _M_IX86
                const uint32_t low = x;
                if (low != 0) {
                    return _tzcnt_u32(low);
                }
                const uint32_t high = static_cast<uint64_t>(x) >> 32;
                return _tzcnt_u32(high) + 32;
#   else  // !defined(_M_IX86)
                return _tzcnt_u64(x);
#   endif
            }
        }

    } // namespace TZCNT


    template <Concept::Integer T>
    [[nodiscard]] __forceinline int CountTrailingZeros(T x) noexcept {
#   ifndef __AVX2__
        if (__isa_available < __ISA_AVAILABLE_AVX2) {
            return BSF::CountTrailingZeros(x);
        }
#   endif
        return TZCNT::CountTrailingZeros(x);
    }

} // namespace Detail::X86_X64

#endif // defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) && !defined(__INTEL_COMPILER)


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountTrailingZeros(T x) noexcept {
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) && !defined(__INTEL_COMPILER)
        if (!__builtin_is_constant_evaluated()) {
            return Detail::X86_X64::CountTrailingZeros(x);
        }
#endif
        return Detail::Common::CountTrailingZeros(x);
    }

} // namespace Bit

#endif
