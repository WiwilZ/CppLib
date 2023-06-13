//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/IntegralTrait.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>

#if defined(_MSC_VER) && !defined(__clang__)

#   if (defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) && !defined(__INTEL_COMPILER)

#define POPCNT_USE_POPCNT_INTRINSICS

#include <isa_availability.h>

extern "C" {
    extern int __isa_available;

    unsigned short __popcnt16(unsigned short);
    unsigned int __popcnt(unsigned int);
    unsigned __int64 __popcnt64(unsigned __int64);
}

#   elif (defined(_M_ARM64) || defined(_M_ARM64EC)) && !defined(_M_CEE_PURE) && !defined(__CUDACC__) && !defined(__INTEL_COMPILER)

#define POPCNT_USE_NEON_INTRINSICS
#include <arm64_neon.h>

#   endif

#endif



namespace Detail {

    namespace Common {

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
            return (PopCountTable[x & 0xFF] << 8) + PopCountTable[x >> 8];
        }

        [[nodiscard]] constexpr int CountOnes(uint32_t x) noexcept {
            x = x - ((x >> 1) & 0x55555555);
            x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
            x = (x + (x >> 4)) & 0xF0F0F0F;
            x = (x * 0x1010101) >> 24;
            return static_cast<int>(x);
        }

        [[nodiscard]] constexpr int CountOnes(uint64_t x) noexcept {
            x = x - ((x >> 1) & 0x5555555555555555);
            x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
            x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
            x = (x * 0x0101010101010101) >> 56;
            return static_cast<int>(x);
        }

#ifdef __SIZEOF_INT128__

        [[nodiscard]] constexpr int CountOnes(__uint128_t x) noexcept {
            constexpr __uint128_t c0 = (__uint128_t{0x5555555555555555} << 64) | 0x5555555555555555;
            constexpr __uint128_t c1 = (__uint128_t{0x3333333333333333} << 64) | 0x3333333333333333;
            constexpr __uint128_t c2 = (__uint128_t{0x0F0F0F0F0F0F0F0F} << 64) | 0x0F0F0F0F0F0F0F0F;
            constexpr __uint128_t c3 = (__uint128_t{0x0101010101010101} << 64) | 0x0101010101010101;
            x = x - ((x >> 1) & c0);
            x = (x & c1) + ((x >> 2) & c1);
            x = (x + (x >> 4)) & c2;
            x = (x * c3) >> 120;
            return static_cast<int>(x);
        }

#endif

    } // namespace Common


#ifdef POPCNT_USE_POPCNT_INTRINSICS

    namespace X86_X64 {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int CountOnes(T x) noexcept {
#   ifndef __AVX2__
            if (__isa_available < __ISA_AVAILABLE_AVX2) {
                return Common::CountOnes(x);
            }
#   endif // __AVX2__
            if constexpr (sizeof(T) <= 2) {
                return __popcnt16(x);
            } else if constexpr (sizeof(T) == 4) {
                return __popcnt(x);
            } else {
#   ifdef _M_IX86
                return __popcnt(x >> 32) + __popcnt(x);
#   else // !defined(_M_IX86)
                return __popcnt64(x);
#   endif
            }
        }

    } // namespace X86_X64

#endif // POPCNT_USE_POPCNT_INTRINSICS


#ifdef POPCNT_USE_NEON_INTRINSICS

    namespace Arm64 {

        [[nodiscard]] __forceinline int CountOnes(uint64_t x) noexcept {
            const __n64 v = neon_cnt(__uint64ToN64_v(x));
            return neon_addv8(v).n8_i8[0];
        }

    } // namespace Arm64

#endif // POPCNT_USE_NEON_INTRINSICS

} // namespace Detail




namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountOnes(T x) noexcept {
        Trait::MakeUnsigned_T<T> ux = x;
#if defined(__GNUC__) || defined(__clang__)
        if constexpr (sizeof(T) <= 4) {
            return __builtin_popcount(ux);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_popcountll(ux);
        } else {
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            return __builtin_popcountll(ux >> 64) + __builtin_popcountll(ux);
        }
#else // !defined(__GNUC__) && !defined(__clang__)
#   if defined(POPCNT_USE_POPCNT_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return Detail::X86_X64::CountOnes(ux);
        }
#   elif defined(POPCNT_USE_NEON_INTRINSICS)
        if (!__builtin_is_constant_evaluated()) {
            return Detail::Arm_Arm64::CountOnes(ux);
        }
#   endif
        return Detail::Common::CountOnes(ux);
#endif
    }

} // namespace Bit



#undef POPCNT_USE_POPCNT_INTRINSICS
#undef POPCNT_USE_NEON_INTRINSICS

