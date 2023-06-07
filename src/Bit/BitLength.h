//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "BitCast.h"
#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>

#if defined(_MSC_VER) && !defined(__clang__)

#   if defined(_M_IX86) || defined(_M_X64) && !defined(_M_ARM64EC)

#define BL_USE_LZCNT_BSR_INTRINSICS

#include <isa_availability.h>

extern "C" {
    extern int __isa_available;

    unsigned short __lzcnt16(unsigned short);
    unsigned int __lzcnt(unsigned int);
    unsigned __int64 __lzcnt64(unsigned __int64);

    unsigned char _BitScanReverse(unsigned long*, unsigned long);
    unsigned char _BitScanReverse64(unsigned long*, unsigned __int64);
}

#   elif defined(_M_ARM) || defined(_M_ARM64)

#define BL_USE_CLZ_INTRINSICS
extern "C" {
    unsigned int _CountLeadingZeros(unsigned long);
    unsigned int _CountLeadingZeros64(unsigned __int64);
}

#   endif

#endif


namespace Detail {

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


    namespace Common {

        [[nodiscard]] constexpr int BitLength(uint16_t x) noexcept {
            return static_cast<int>(Bit::BitCast<uint32_t>(static_cast<float>(x)) >> 23) - 0x7f + 1;
        }

        [[nodiscard]] constexpr int BitLength(uint32_t x) noexcept {
            return static_cast<int>(Bit::BitCast<uint64_t>(static_cast<double>(x)) >> 52) - 0x3ff + 1;
        }

        [[nodiscard]] constexpr int BitLength(uint64_t x) noexcept {
#ifdef __AVX512F__
            if (!__builtin_is_constant_evaluated()) {
                __m128 tmp;
                float v = _mm_cvtss_f32(_mm_cvt_roundu64_ss(tmp, x, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
                return static_cast<int>(::BitCast<uint32_t>(v) >> 23) - 0x7f + 1;
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
        [[nodiscard]] constexpr __uint128_t BitLength(__uint128_t x) noexcept {
            int n = 0;
            if (x >= __uint128_t{1} << 64) {
                x >>= 64;
                n = 64;
            }
            if (x >= __uint128_t{1} << 32) {
                x >>= 32;
                n += 32;
            }
            if (x >= __uint128_t{1} << 16) {
                x >>= 16;
                n += 16;
            }
            if (x >= __uint128_t{1} << 8) {
                x >>= 8;
                n += 8;
            }
            return n + BitLengthTable[x];
        }
#endif

    } // namespace Common


#ifdef BL_USE_LZCNT_BSR_INTRINSICS

    namespace LZCNT {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLength(T x) noexcept {
            if constexpr (sizeof(T) <= 2) {
                return 16 - __lzcnt16(x);
            } else if constexpr (sizeof(T) == 4) {
                return 32 - __lzcnt(x);
            } else {
#   ifdef _M_IX86
                const uint32_t high = x >> 32;
                if (high != 0) {
                    return 64 - __lzcnt(high);
                }
                const uint32_t low = x;
                return 32 - __lzcnt(low);
#   else // !defined(_M_IX86)
                return 64 - static_cast<int>(__lzcnt64(x));
#   endif
            }
        }

    } // namespace LZCNT


    namespace BSR {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLength(T x) noexcept {
            unsigned long result;
            if constexpr (sizeof(T) <= 4) {
                if (_BitScanReverse(&result, x)) {
                    return result + 1;
                }
                return 0;
            } else {
#   ifdef _M_IX86
                const uint32_t high = x >> 32;
                if (_BitScanReverse(&result, high)) {
                    return result + 1 + 32;
                }
                const uint32_t low = x;
                if (_BitScanReverse(&result, low)) {
                    return result + 1;
                }
#   else // !defined(_M_IX86)
                if (_BitScanReverse64(&result, x)) {
                    return result + 1;
                }
#   endif
                return 0;
            }
        }

    } // namespace BSR


    namespace X86_X64 {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] __forceinline int BitLength(T x) noexcept {
#   ifndef __AVX2__
            if (__isa_available < __ISA_AVAILABLE_AVX2) {
                return BSR::BitLength(x);
            }
#   endif
            return LZCNT::BitLength(x);
        }

    } // namespace X86_X64

#endif // BL_USE_LZCNT_BSR_INTRINSICS


#ifdef BL_USE_CLZ_INTRINSICS

    namespace Arm_Arm64 {

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

    } // namespace Arm_Arm64

#endif // BL_USE_CLZ_INTRINSICS


    namespace MSVC {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] constexpr int BitLength(T x) noexcept {
#ifdef _MSC_VER
#   if defined(BL_USE_LZCNT_BSR_INTRINSICS)
            if (!__builtin_is_constant_evaluated()) {
                return X86_X64::BitLength(x);
            }
#   elif defined(BL_USE_CLZ_INTRINSICS)
            if (!__builtin_is_constant_evaluated()) {
                return Arm_Arm64::BitLength(x);
            }
#   endif
#endif
            return Common::BitLength(x);
        }

    } // namespace MSVC



    [[nodiscard]] constexpr int BitLength(uint8_t x) noexcept {
        return BitLengthTable[x];
    }

    [[nodiscard]] constexpr int BitLength(uint16_t x) noexcept {
#if __has_builtin(__builtin_clzs)
        return 16 - __builtin_clzs(x);
#elif __has_builtin(__builtin_clz)
        return 32 - __builtin_clz(x);
#else // !__has_builtin(__builtin_clzs) && !__has_builtin(__builtin_clz)
        return MSVC::BitLength(x);
#endif
    }

    [[nodiscard]] constexpr int BitLength(uint32_t x) noexcept {
#if __has_builtin(__builtin_clz)
        return 32 - __builtin_ctz(x);
#else // !__has_builtin(__builtin_clz)
        return MSVC::BitLength(x);
#endif
    }

    [[nodiscard]] constexpr int BitLength(uint64_t x) noexcept {
#if __has_builtin(__builtin_clzll)
        return 64 - __builtin_clzll(x);
#else // !__has_builtin(__builtin_clzll)
        return MSVC::BitLength(x);
#endif
    }

#ifdef __SIZEOF_INT128__

    [[nodiscard]] constexpr int BitLength(__uint128_t x) noexcept {
#if __has_builtin(__builtin_clzll)
        const uint64_t high = x >> 64;
        if (high != 0) {
            return 128 - __builtin_clzll(high);
        }
        const uint64_t low = x;
        return 64 - __builtin_clzll(low);
#else // !__has_builtin(__builtin_clzll)
        return Common::BitLength(x);
#endif
    }

#endif

} // namespace Detail



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int BitLength(T x) noexcept {
        return Detail::BitLength(static_cast<Trait::MakeUnsigned_T<T>>(x));
    }

} // namespace Bit



#undef BL_USE_LZCNT_BSR_INTRINSICS
#undef BL_USE_CLZ_INTRINSICS
