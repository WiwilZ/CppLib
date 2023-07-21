//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concepts/Integral.h"
#include "../Concepts/UnsignedInteger.h"
#include "../Traits/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>



#if defined(_MSC_VER) && !defined(__clang__)
#   if defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)
#define USE_X86_INTRINSICS
#include <isa_availability.h>
extern "C" {
    extern int __isa_available;

    unsigned int __popcnt(unsigned int);
    unsigned __int64 __popcnt64(unsigned __int64);
}
#   elif (defined(_M_ARM64) || defined(_M_ARM64EC)) && !defined(_M_CEE_PURE)
#define USE_ARM_INTRINSICS
#include <arm64_neon.h>
#   endif
#endif // defined(_MSC_VER) && !defined(__clang__)



namespace detail {
    namespace common {
        static constexpr uint8_t PopCountTable[256]{
                0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
                1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
        };

        [[nodiscard]] constexpr int CountOnes(uint8_t x) noexcept {
            return PopCountTable[x];
        }

        [[nodiscard]] constexpr int CountOnes(uint16_t x) noexcept {
            return PopCountTable[x >> 8] + PopCountTable[x & 0xFF];
        }

        [[nodiscard]] constexpr int CountOnes(uint32_t x) noexcept {
            x -= (x >> 1) & 0x55555555;
            x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
            x = (x + (x >> 4)) & 0xF0F0F0F;
            x = (x * 0x01010101) >> 24;
            return x;
        }

        [[nodiscard]] constexpr int CountOnes(uint64_t x) noexcept {
            x -= (x >> 1) & 0x5555555555555555;
            x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
            x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
            x = (x * 0x0101010101010101) >> 56;
            return x;
        }

#ifdef __SIZEOF_INT128__
        [[nodiscard]] constexpr int CountOnes(__uint128_t x) noexcept {
            constexpr __uint128_t C0 = (__uint128_t{0x5555555555555555} << 64) | 0x5555555555555555;
            constexpr __uint128_t C1 = (__uint128_t{0x3333333333333333} << 64) | 0x3333333333333333;
            constexpr __uint128_t C2 = (__uint128_t{0x0F0F0F0F0F0F0F0F} << 64) | 0x0F0F0F0F0F0F0F0F;
            constexpr __uint128_t C3 = (__uint128_t{0x0101010101010101} << 64) | 0x0101010101010101;
            x -= (x >> 1) & C0;
            x = (x & C1) + ((x >> 2) & C1);
            x = (x + (x >> 4)) & C2;
            x = (x * C3) >> 120;
            return x;
        }
#endif
    } // namespace common



#ifdef USE_X86_INTRINSICS
    namespace x86 {
        template <concepts::UnsignedInteger T>
        [[nodiscard]] __forceinline int CountOnes(T x) noexcept {
#   ifndef __AVX2__
            if (__isa_available < __ISA_AVAILABLE_AVX2) {
                return common::CountOnes(x);
            }
#   endif // __AVX2__
            if constexpr (sizeof(T) <= 4) {
                return __popcnt(x);
            } else {
#   ifdef _M_IX86
                return __popcnt(x >> 32) + __popcnt(x);
#   else // !defined(_M_IX86)
                return __popcnt64(x);
#   endif
            }
        }
    } // namespace x86
#elif defined(USE_ARM_INTRINSICS)
    namespace arm {
        [[nodiscard]] __forceinline int CountOnes(uint64_t x) noexcept {
            const __n64 v = neon_cnt(__uint64ToN64_v(x));
            return neon_addv8(v).n8_i8[0];
        }
    } // namespace arm
#endif



    template <concepts::UnsignedInteger T>
    requires (sizeof(T) <= 4)
    [[nodiscard]] constexpr int CountOnes(T x) noexcept {
#if HAS_BUILTIN(__builtin_popcount)
        return __builtin_popcount(x);
#else // !HAS_BUILTIN(__builtin_popcount)
#   ifdef USE_X86_INTRINSICS
        if (!__builtin_is_constant_evaluated()) {
            return x86::CountOnes(x);
        }
#   elif defined(USE_ARM_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return arm::CountOnes(x);
        }
#   endif
        return common::CountOnes(x);
#endif
    }

    [[nodiscard]] constexpr int CountOnes(uint64_t x) noexcept {
#if HAS_BUILTIN(__builtin_popcountll)
        return __builtin_popcountll(x);
#else // !HAS_BUILTIN(__builtin_popcountll)
#   ifdef USE_X86_INTRINSICS
        if (!__builtin_is_constant_evaluated()) {
            return x86::CountOnes(x);
        }
#   elif defined(USE_ARM_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return arm::CountOnes(x);
        }
#   endif
        return common::CountOnes(x);
#endif
    }

#ifdef __SIZEOF_INT128__
    [[nodiscard]] constexpr int CountOnes(__uint128_t x) noexcept {
#if HAS_BUILTIN(__builtin_popcountll)
        return __builtin_popcountll(x >> 64) + __builtin_popcountll(x);
#else // !HAS_BUILTIN(__builtin_popcountll)
        return common::CountOnes(x);
#endif
    }
#endif // __SIZEOF_INT128__
} // namespace detail



#undef USE_X86_INTRINSICS
#undef USE_ARM_INTRINSICS



template <concepts::Integral T>
[[nodiscard]] constexpr int CountOnes(T x) noexcept {
    return detail::CountOnes(static_cast<traits::MakeUInt_T<sizeof(T)>>(x));
}




