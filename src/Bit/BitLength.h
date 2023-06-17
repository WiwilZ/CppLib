//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "BitCast.h"
#include "../Concept/UnsignedInteger.h"
#include "../Concept/Integral.h"
#include "../Trait/MakeIntegerType.h"
#include "../Macro.h"

#include <cstdint>



#ifdef __AVX512F__
#include <immintrin.h>
#endif



#if defined(_MSC_VER) && !defined(__clang__) && !defined(__CUDACC__) && !defined(__INTEL_COMPILER)
#   if defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)
#define USE_X86_INTRINSICS
#       ifndef __AVX2__
#include <isa_availability.h>
extern "C" {
    extern int __isa_available;

    unsigned char _BitScanReverse(unsigned long*, unsigned long);
    unsigned char _BitScanReverse64(unsigned long*, unsigned __int64);
}
#       endif // __AVX2__
extern "C" {
    unsigned int __lzcnt(unsigned int);
    unsigned __int64 __lzcnt64(unsigned __int64);
}
#   elif defined(_M_ARM) || defined(_M_ARM64)
#define USE_ARM_INTRINSICS
extern "C" {
    unsigned int _CountLeadingZeros(unsigned long);
    unsigned int _CountLeadingZeros64(unsigned __int64);
}
#   endif
#endif // defined(_MSC_VER) && !defined(__clang__)



namespace Detail {
    namespace Common {
        static constexpr uint8_t BitLengthTable[256] {
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

        [[nodiscard]] constexpr int BitLength(uint8_t x) noexcept {
            return BitLengthTable[x];
        }

        [[nodiscard]] constexpr int BitLength(uint16_t x) noexcept {
            return (Bit::BitCast<uint32_t>(static_cast<float>(x)) >> 23) - 0x7f + 1;
        }

        [[nodiscard]] constexpr int BitLength(uint32_t x) noexcept {
            return (Bit::BitCast<uint64_t>(static_cast<double>(x)) >> 52) - 0x3ff + 1;
        }

        [[nodiscard]] constexpr int BitLength(uint64_t x) noexcept {
#ifdef __AVX512F__
            if (!__builtin_is_constant_evaluated()) {
                const float v = _mm_cvtss_f32(_mm_cvt_roundu64_ss(__m128{}, x, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
                return (Bit::BitCast<uint32_t>(v) >> 23) - 0x7f + 1;
            }
#endif
            const uint32_t high = x >> 32;
            if (high != 0) {
                return 32 + BitLength(high);
            }
            const uint32_t low = x;
            return BitLength(low);
        }

#ifdef __SIZEOF_INT128__
        [[nodiscard]] constexpr int BitLength(__uint128_t x) noexcept {
//            int n = 0;
//            if (static_cast<uint64_t>(x >> 64) & ~uint64_t{}) {
//                x >>= 64;
//                n = 64;
//            }
//            if (static_cast<uint32_t>(x >> 32) & ~uint32_t{}) {
//                x >>= 32;
//                n += 32;
//            }
//            if (static_cast<uint16_t>(x >> 16) & ~uint16_t{}) {
//                x >>= 16;
//                n += 16;
//            }
//            if (static_cast<uint8_t>(x >> 8) & ~uint8_t{}) {
//                x >>= 8;
//                n += 8;
//            }
//            return n + BitLengthTable[x];
            const uint64_t high = x >> 64;
            if (high != 0) {
                return 64 + BitLength(high);
            }
            const uint64_t low = x;
            return BitLength(low);
        }
#endif
    } // namespace Common



#ifdef USE_X86_INTRINSICS
    namespace X86 {
#   ifndef __AVX2__
        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLengthByBSR(T x) noexcept {
            unsigned long result;
            if constexpr (sizeof(T) <= 4) {
                if (_BitScanReverse(&result, x)) {
                    return result + 1;
                }
            } else {
#       ifdef _M_IX86
                const uint32_t high = x >> 32;
                if (_BitScanReverse(&result, high)) {
                    return result + 1 + 32;
                }
                const uint32_t low = x;
                if (_BitScanReverse(&result, low)) {
                    return result + 1;
                }
#       else // !defined(_M_IX86)
                if (_BitScanReverse64(&result, x)) {
                    return result + 1;
                }
#       endif
            }
            return 0;
        }
#   endif // !defined(__AVX2__)

        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLengthByLZCNT(T x) noexcept {
            if constexpr (sizeof(T) <= 4) {
                return 32 - __lzcnt(x);
            } else {
#       ifdef _M_IX86
                const uint32_t high = x >> 32;
                if (high != 0) {
                    return 64 - __lzcnt(high);
                }
                const uint32_t low = x;
                return 32 - __lzcnt(low);
#       else // !defined(_M_IX86)
                return 64 - __lzcnt64(x);
#       endif
            }
        }

        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLength(T x) noexcept {
#   ifndef __AVX2__
            if (__isa_available < __ISA_AVAILABLE_AVX2) {
                return BitLengthByBSR(x);
            }
#   endif
            return BitLengthByLZCNT(x);
        }
    } // namespace X86
#elif defined(USE_ARM_INTRINSICS)
    namespace Arm {
        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLength(T x) noexcept {
            if (x == 0) {
                return 0;
            }
            if constexpr (sizeof(T) <= 4) {
                return 32 - _CountLeadingZeros(x);
            } else {
                return 64 - _CountLeadingZeros64(x);
            }
        }
    } // namespace Arm
#endif



    template <Concept::UnsignedInteger T>
    requires (sizeof(T) <= 4)
    [[nodiscard]] constexpr int BitLength(T x) noexcept {
#if HAS_BUILTIN(__builtin_clz)
        return 32 - __builtin_clz(x);
#else // !HAS_BUILTIN(__builtin_clz)
#   ifdef USE_X86_INTRINSICS
        if (!__builtin_is_constant_evaluated()) {
            return X86::BitLength(x);
        }
#   elif defined(USE_ARM_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return Arm::BitLength(x);
        }
#   endif
        return Common::BitLength(x);
#endif
    }

    [[nodiscard]] constexpr int BitLength(uint64_t x) noexcept {
#if HAS_BUILTIN(__builtin_clzll)
        return 64 - __builtin_clzll(x);
#else // !HAS_BUILTIN(__builtin_clzll)
#   ifdef USE_X86_INTRINSICS
        if (!__builtin_is_constant_evaluated()) {
            return X86::BitLength(x);
        }
#   elif defined(USE_ARM_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return Arm::BitLength(x);
        }
#   endif
        return Common::BitLength(x);
#endif
    }

#ifdef __SIZEOF_INT128__
    [[nodiscard]] constexpr int BitLength(__uint128_t x) noexcept {
#if HAS_BUILTIN(__builtin_clzll)
        const uint64_t high = x >> 64;
        if (high != 0) {
            return 128 - __builtin_clzll(high);
        }
        const uint64_t low = x;
        return 64 - __builtin_clzll(low);
#else
        return Common::BitLength(x);
#endif
    }
#endif // __SIZEOF_INT128__
} // namespace Detail



namespace Bit {
    template <Concept::Integral T>
    [[nodiscard]] constexpr int BitLength(T x) noexcept {
        return Detail::BitLength(static_cast<Trait::MakeUInt_T<sizeof(T)>>(x));
    }
}



#undef USE_X86_INTRINSICS
#undef USE_X86_64_INTRINSICS

