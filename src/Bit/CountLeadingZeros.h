//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include <cstdint>
#include "../Macro.h"
#include "../Concept.h"
#include "../Trait.h"


#if !(defined(__GNUC__) || defined(__clang__))
#include "Common/BitLength.h"
#endif


#if defined(_MSC_VER) && !defined(__clang__)
#   if defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)
#       define USE_LZCNT_BSR_INTRINSICS
#       include <intrin.h>
#       include <isa_availability.h>
        extern "C" {
            extern int __isa_available;
        }

#   elif defined(_M_ARM) || defined(_M_ARM64)
#       define USE_CLZ_INTRINSICS
#       include <intrin.h>
#   endif
#endif


namespace Detail {

#if !(defined(__GNUC__) || defined(__clang__))

    namespace Common {
        template <UnsignedIntegral T>
        constexpr int CountLeadingZeros(T x) noexcept {
            return IntegralTrait<T>::NumBits - BitLength(x);
        }
    } // namespace Common

#endif


#ifdef USE_LZCNT_BSR_INTRINSICS

    namespace LZCNT {

        template <UnsignedIntegral T>
        FORCEINLINE int CountLeadingZeros(T x) noexcept {
            constexpr int NumBits = IntegralTrait<T>::NumBits;
            if constexpr (sizeof(T) <= 2) {
                return __lzcnt16(x) - (16 - NumBits);
            } else if constexpr (sizeof(T) == 4) {
                return __lzcnt(x);
            } else {
#   ifdef _M_IX86
                const uint32_t high = x >> 32;
                if (high != 0) {
                    return __lzcnt(high);
                }
                const uint32_t low = x;
                return 32 + __lzcnt(low);
#   else
                return static_cast<int>(__lzcnt64(x));
#   endif // _M_IX86
            }
        }

    } // namespace LZCNT

    namespace BSR {

        template <UnsignedIntegral T>
        FORCEINLINE int CountLeadingZeros(T x) noexcept {
            constexpr int NumBits = IntegralTrait<T>::NumBits;
            unsigned long result;
            if constexpr (sizeof(T) <= 4) {
                if (!_BitScanReverse(&result, x)) {
                    return NumBits;
                }
            } else {
#   ifdef _M_IX86
                const uint32_t high = x >> 32;
                if (_BitScanReverse(&result, high)) {
                    return 31 - result;
                }
                const uint32_t low = x;
                if (!_BitScanReverse(&result, low)) {
                    return NumBits;
                }
#   else
                if (!_BitScanReverse64(&result, x)) {
                    return NumBits;
                }
#   endif // _M_IX86
            }
            return NumBits - 1 - result;
        }

    } // namespace BSR

    namespace X86_X64 {

        template <UnsignedIntegral T>
        FORCEINLINE int CountLeadingZeros(T x) noexcept {
#   ifdef __AVX2__
            return LZCNT::CountLeadingZeros(x);
#   else
            if (__isa_available >= __ISA_AVAILABLE_AVX2) {
                return LZCNT::CountLeadingZeros(x);
            } else {
                return BSR::CountLeadingZeros(x);
            }
#   endif // __AVX2__
        }

    } // namespace X86_X64

#endif // USE_LZCNT_BSR_INTRINSICS


#ifdef USE_CLZ_INTRINSICS

    namespace Arm_Arm64 {

        template <UnsignedIntegral T>
        FORCEINLINE int CountLeadingZeros(T x) noexcept {
            constexpr int NumBits = IntegralTrait<T>::NumBits;
            if (x == 0) {
                return NumBits;
            }
            if constexpr (sizeof(T) <= 4) {
                return _CountLeadingZeros(x)) - (32 - NumBits);
            } else {
                return _CountLeadingZeros64(x);
            }
        }

    } // namespace Arm_Arm64

#endif // USE_CLZ_INTRINSICS

} // namespace Detail



template <UnsignedIntegral T>
[[nodiscard]] constexpr int CountLeadingZeros(T x) noexcept {
    constexpr int NumBits = IntegralTrait<T>::NumBits;
#if defined(__GNUC__) || defined(__clang__)
#ifdef __clang__
    if constexpr (sizeof(T) <= 2) {
        return __builtin_clzs(x) - (16 - NumBits);
    } else if constexpr (sizeof(T) == 4) {
        return __builtin_clz(x);
    }
#else
    if constexpr (sizeof(T) <= 4) {
        return __builtin_clz(x) - (32 - NumBits);
    }
#endif // defined(__GNUC__) || defined(__clang__)
    else if constexpr (sizeof(T) == 8) {
        return __builtin_clzll(x);
    } else {
        const uint64_t high = x >> 64;
        if (high != 0) {
            return __builtin_clzll(high);
        }
        const uint64_t low = x;
        return 64 + __builtin_clzll(low);
    }
#elif defined(_MSC_VER)
#   if defined(USE_LZCNT_BSR_INTRINSICS)
    if (!__builtin_is_constant_evaluated()) {
        return Detail::X86_X64::CountLeadingZeros(x);
    }
#   elif defined(USE_CLZ_INTRINSICS)
    if (!__builtin_is_constant_evaluated()) {
        return Detail::Arm_Arm64::CountLeadingZeros(x);
    }
#   endif
    return NumBits - Detail::Common::BitLength(x);
#else
    return NumBits - Detail::Common::BitLength(x);
#endif
}



