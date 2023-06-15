//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "BitCast.h"
#include "../Concept/Integer.h"

#include <cstdint>
#include <climits>



#if defined(__GNUC__) || defined(__clang__)

namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountLeadingZeros(T x) noexcept {
        if constexpr (sizeof(T) <= 4) {
            return __builtin_clz(x) - (32 - sizeof(T) * CHAR_BIT);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_clzll(x);
        } else {
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            const uint64_t high = static_cast<__uint128_t>(x) >> 64;
            if (high != 0) {
                return __builtin_clzll(high);
            }
            const uint64_t low = x;
            return 64 + __builtin_clzll(low);
        }
    }

    
    template <Concept::Integer T>
    [[nodiscard]] constexpr int BitLength(T x) noexcept {
        return sizeof(T) * CHAR_BIT - CountLeadingZeros(x);
    }
    
} // namespace Bit

#else // !defined(__GNUC__) && !defined(__clang__)

#ifdef __AVX512F__
#include <immintrin.h>
#endif


namespace Detail::Common {

    static constexpr uint8_t BitLengthTable[256]{
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
    };


    template <Concept::Integer T>
    [[nodiscard]] constexpr int BitLength(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return BitLengthTable[static_cast<uint8_t>(x)];
        } else if constexpr (sizeof(T) == 2) {
            return (Bit::BitCast<uint32_t>(static_cast<float>(static_cast<uint16_t>(x))) >> 23) - 0x7f + 1;
        } else if constexpr (sizeof(T) == 4) {
            return (Bit::BitCast<uint64_t>(static_cast<double>(static_cast<uint32_t>(x))) >> 52) - 0x3ff + 1;
        } else if constexpr (sizeof(T) == 8) {
#ifdef __AVX512F__
            if (!__builtin_is_constant_evaluated()) {
                float v = _mm_cvtss_f32(_mm_cvt_roundu64_ss(__m128{}, x, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
                return (Bit::BitCast<uint32_t>(v) >> 23) - 0x7f + 1;
            }
#endif
            const uint32_t high = static_cast<uint64_t>(x) >> 32;
            if (high != 0) {
                return 32 + BitLength(high);
            }
            const uint32_t low = x;
            return BitLength(low);
        } else {
#ifdef __SIZEOF_INT128__
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            __uint128_t ux = x;
            int n = 0;
            if (ux >= __uint128_t{1} << 64) {
                ux >>= 64;
                n = 64;
            }
            if (ux >= __uint128_t{1} << 32) {
                ux >>= 32;
                n += 32;
            }
            if (ux >= __uint128_t{1} << 16) {
                ux >>= 16;
                n += 16;
            }
            if (ux >= __uint128_t{1} << 8) {
                ux >>= 8;
                n += 8;
            }
            return n + BitLengthTable[ux];
#else
            static_assert(sizeof(T) <= 8, "Unexpected integer size");
#endif
        }
    }



    static constexpr uint8_t LeadingZerosTable[256]{
        8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };


    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountLeadingZeros(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return LeadingZerosTable[static_cast<uint8_t>(x)];
        } else if constexpr (sizeof(T) <= 8) {
            return sizeof(T) * CHAR_BIT - BitLength(x);
        } else {
#ifdef __SIZEOF_INT128__
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            __uint128_t ux = x;
            int n = 128;
            if (ux >= __uint128_t{1} << 64) {
                ux >>= 64;
                n = 64;
            }
            if (ux >= __uint128_t{1} << 32) {
                ux >>= 32;
                n -= 32;
            }
            if (ux >= __uint128_t{1} << 16) {
                ux >>= 16;
                n -= 16;
            }
            if (ux >= __uint128_t{1} << 8) {
                ux >>= 8;
                n -= 8;
            }
            return n + LeadingZerosTable[x];
#else
            static_assert(sizeof(T) <= 8, "Unexpected integer size");
#endif
        }
    }

} // namespace Detail::Common



#ifdef _MSC_VER

#if defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)

#ifndef __AVX2__

#include <isa_availability.h>
extern "C" {
    extern int __isa_available;

    unsigned char _BitScanReverse(unsigned long*, unsigned long);
    unsigned char _BitScanReverse64(unsigned long*, unsigned __int64);
}


namespace Detail::X86_X64::BSR {

    template <Concept::Integer T>
    [[nodiscard]] __forceinline int CountLeadingZeros(T x) noexcept {
        unsigned long result;
        if constexpr (sizeof(T) <= 4) {
            constexpr int NumBits = sizeof(T) * CHAR_BIT;
            if (_BitScanReverse(&result, x)) {
                return NumBits - (result + 1);
            }
            return NumBits;
        } else {
            static_assert(sizeof(T) == 8, "Unexpected integer size");
#ifdef _M_IX86
            const uint32_t high = static_cast<uint64_t>(x) >> 32;
            if (_BitScanReverse(&result, high)) {
                return 32 - (result + 1);
            }
            const uint32_t low = x;
            if (_BitScanReverse(&result, low)) {
                return 64 - (result + 1);
            }
#else // !defined(_M_IX86)
            if (_BitScanReverse64(&result, x)) {
                return 64 - (result + 1);
            }
#endif
            return 64;
        }
    }

} // namespace Detail::X86_X64::BSR

#endif // !defined(__AVX2__)

extern "C" {
    unsigned int __lzcnt(unsigned int);
    unsigned __int64 __lzcnt64(unsigned __int64);
}

namespace Detail::X86_X64 {

    namespace LZCNT {

        template <Concept::Integer T>
        [[nodiscard]] __forceinline int CountLeadingZeros(T x) noexcept {
            if constexpr (sizeof(T) <= 4) {
                return __lzcnt(x) - (32 - sizeof(T) * CHAR_BIT);
            } else {
                static_assert(sizeof(T) == 8, "Unexpected integer size");
#ifdef _M_IX86
                const uint32_t high = static_cast<uint64_t>(x) >> 32;
                if (high != 0) {
                    return __lzcnt(high);
                }
                const uint32_t low = x;
                return 32 + __lzcnt(low);
#else // !defined(_M_IX86)
                return __lzcnt64(x);
#endif
            }
        }

    } // namespace LZCNT


    template <Concept::Integer T>
    [[nodiscard]] __forceinline int CountLeadingZeros(T x) noexcept {
#ifndef __AVX2__
        if (__isa_available < __ISA_AVAILABLE_AVX2) {
            return BSR::CountLeadingZeros(x);
        }
#endif
        return LZCNT::CountLeadingZeros(x);
    }

} // namespace Detail::X86_X64

#elif defined(_M_ARM) || defined(_M_ARM64)

extern "C" {
    unsigned int _CountLeadingZeros(unsigned long);
    unsigned int _CountLeadingZeros64(unsigned __int64);
}


namespace Detail::Arm_Arm64 {

    template <Concept::Integer T>
    [[nodiscard]] __forceinline int CountLeadingZeros(T x) noexcept {
        constexpr int NumBits = sizeof(T) * CHAR_BIT;
        if (x == 0) {
            return NumBits;
        }
        if constexpr (sizeof(T) <= 4) {
            return _CountLeadingZeros(x) - (32 - NumBits);
        } else {
            static_assert(sizeof(T) == 8, "Unexpected integer size");
            return _CountLeadingZeros64(x);
        }
    }

} // namespace Detail::Arm_Arm64

#endif

#endif // defined(_MSC_VER)


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountLeadingZeros(T x) noexcept {
#if defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)
        if (!__builtin_is_constant_evaluated()) {
            return Detail::X86_X64::CountLeadingZeros(x);
        }
#elif defined(_M_ARM) || defined(_M_ARM64)
        if (!__builtin_is_constant_evaluated()) {
            return Detail::Arm_Arm64::CountLeadingZeros(x);
        }
#endif
        return Detail::Common::CountLeadingZeros(x);
    }


    template <Concept::Integer T>
    [[nodiscard]] constexpr int BitLength(T x) noexcept {
#if defined(USE_X86_64_INTRINSICS) || defined(USE_ARM_ARM64_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return sizeof(T) * CHAR_BIT - CountLeadingZeros(x);
        }
#endif
        return Detail::Common::BitLength(x);
    }

} // namespace Bit

#endif


