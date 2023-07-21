//
// Created by WiwilZ on 2023/5/30.
//

#pragma once


#include "../Concepts/UnsignedInteger.h"
#include "../Concepts/Integral.h"
#include "../Traits/MakeIntegerType.h"
#include "../ArithmeticType.h"
#include "../Macro.h"


#if defined(_MSC_VER) && !defined(__clang__)
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



#ifdef __AVX512F__
#include <xmmintrin.h>
#include <immintrin.h>
#endif



namespace detail {
    namespace common {
        static constexpr u8 BitLengthTable[256] {
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

        [[nodiscard]] constexpr usize BitLength(u8 x) noexcept {
            return BitLengthTable[x];
        }

        [[nodiscard]] constexpr usize BitLength(u16 x) noexcept {
            return (__builtin_bit_cast(u32, static_cast<float>(x)) >> 23) - 0x7f + 1;
        }

        [[nodiscard]] constexpr usize BitLength(u32 x) noexcept {
            return (__builtin_bit_cast(u64, static_cast<double>(x)) >> 52) - 0x3ff + 1;
        }

        [[nodiscard]] constexpr usize BitLength(u64 x) noexcept {
#ifdef __AVX512F__
            if (!__builtin_is_constant_evaluated()) {
                const float v = _mm_cvtss_f32(_mm_cvt_roundu64_ss(_mm_undefined_ps(), x, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
                return (__builtin_bit_cast(uint32_t, v) >> 23) - 0x7f + 1;
            }
#endif
            const u32 high = x >> 32;
            if (high != 0) {
                return 32 + BitLength(high);
            }
            const u32 low = x;
            return BitLength(low);
        }

#if HAS_INT128
        [[nodiscard]] constexpr usize BitLength(u128 x) noexcept {
//            int n = 0;
//            if (static_cast<u64>(x >> 64) & ~u64{}) {
//                x >>= 64;
//                n = 64;
//            }
//            if (static_cast<u32>(x >> 32) & ~u32{}) {
//                x >>= 32;
//                n += 32;
//            }
//            if (static_cast<u16>(x >> 16) & ~u16{}) {
//                x >>= 16;
//                n += 16;
//            }
//            if (static_cast<u8>(x >> 8) & ~u8{}) {
//                x >>= 8;
//                n += 8;
//            }
//            return n + BitLengthTable[x];
            const u64 high = x >> 64;
            if (high != 0) {
                return 64 + BitLength(high);
            }
            const u64 low = x;
            return BitLength(low);
        }
#endif
    } // namespace common



#ifdef USE_X86_INTRINSICS
    namespace x86 {
#   ifndef __AVX2__
        template <concepts::UnsignedInteger T>
        [[nodiscard]] __forceinline usize BitLengthByBSR(T x) noexcept {
            unsigned long result;
            if constexpr (sizeof(T) <= 4) {
                if (_BitScanReverse(&result, x)) {
                    return result + 1;
                }
            } else {
#       ifdef _M_IX86
                const u32 high = x >> 32;
                if (_BitScanReverse(&result, high)) {
                    return result + 1 + 32;
                }
                const u32 low = x;
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

        template <concepts::UnsignedInteger T>
        [[nodiscard]] __forceinline usize BitLengthByLZCNT(T x) noexcept {
            if constexpr (sizeof(T) <= 4) {
                return 32 - __lzcnt(x);
            } else {
#       ifdef _M_IX86
                const u32 high = x >> 32;
                if (high != 0) {
                    return 64 - __lzcnt(high);
                }
                const u32 low = x;
                return 32 - __lzcnt(low);
#       else // !defined(_M_IX86)
                return 64 - __lzcnt64(x);
#       endif
            }
        }

        template <concepts::UnsignedInteger T>
        [[nodiscard]] __forceinline usize BitLength(T x) noexcept {
#   ifndef __AVX2__
            if (__isa_available < __ISA_AVAILABLE_AVX2) {
                return BitLengthByBSR(x);
            }
#   endif
            return BitLengthByLZCNT(x);
        }
    } // namespace x86
#elif defined(USE_ARM_INTRINSICS)
    namespace arm {
        template <concepts::UnsignedInteger T>
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
    } // namespace arm
#endif



    template <concepts::UnsignedInteger T>
    requires (sizeof(T) <= 4)
    [[nodiscard]] constexpr usize BitLength(T x) noexcept {
#if HAS_BUILTIN(__builtin_clz)
        return 32 - __builtin_clz(x);
#else // !HAS_BUILTIN(__builtin_clz)
#   ifdef USE_X86_INTRINSICS
        if (!__builtin_is_constant_evaluated()) {
            return x86::BitLength(x);
        }
#   elif defined(USE_ARM_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return arm::BitLength(x);
        }
#   endif
        return common::BitLength(x);
#endif
    }

    [[nodiscard]] constexpr usize BitLength(u64 x) noexcept {
#if HAS_BUILTIN(__builtin_clzll)
        return 64 - __builtin_clzll(x);
#else // !HAS_BUILTIN(__builtin_clzll)
#   ifdef USE_X86_INTRINSICS
        if (!__builtin_is_constant_evaluated()) {
            return x86::BitLength(x);
        }
#   elif defined(USE_ARM_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return arm::BitLength(x);
        }
#   endif
        return common::BitLength(x);
#endif
    }

#if HAS_INT128
    [[nodiscard]] constexpr usize BitLength(u128 x) noexcept {
#if HAS_BUILTIN(__builtin_clzll)
        const u64 high = x >> 64;
        if (high != 0) {
            return 128 - __builtin_clzll(high);
        }
        const u64 low = x;
        return 64 - __builtin_clzll(low);
#else
        return common::BitLength(x);
#endif
    }
#endif
} // namespace detail



#undef USE_X86_INTRINSICS
#undef USE_ARM_INTRINSICS



template <concepts::Integral T>
[[nodiscard]] constexpr usize BitLength(T x) noexcept {
    return detail::BitLength(static_cast<traits::MakeUInt_T<sizeof(T)>>(x));
}

