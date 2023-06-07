//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/IntegralTrait.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>

#ifdef _MSC_VER

extern "C" {
    unsigned char _rotl8(unsigned char, unsigned char);
    unsigned short _rotl16(unsigned short, unsigned char);
    unsigned int _rotl(unsigned int, int);
    unsigned __int64 _rotl64(unsigned __int64, int);
}

#endif



namespace Detail {

    namespace Common {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] constexpr T LeftCircularShift(T x, unsigned n) noexcept {
            constexpr int NumBits = Trait::IntegralTrait<T>::NumBits;
            n %= NumBits;
            if (n == 0) {
                return x;
            }
            return (x << n) | (x >> (NumBits - n));
        }

    } // namespace Common



    [[nodiscard]] constexpr uint8_t LeftCircularShift(uint8_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateleft8)
        return __builtin_rotateleft8(x, n);
#else // __has_builtin(__builtin_rotateleft8)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl8(x, n);
        }
#   endif
        return Common::LeftCircularShift(x, n);
#endif
    }

    [[nodiscard]] constexpr uint16_t LeftCircularShift(uint16_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateleft16)
        return __builtin_rotateleft16(x, n);
#else // __has_builtin(__builtin_rotateleft16)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl16(x, n);
        }
#   endif
        return Common::LeftCircularShift(x, n);
#endif
    }

    [[nodiscard]] constexpr uint32_t LeftCircularShift(uint32_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateleft32)
        return __builtin_rotateleft32(x, n);
#else // __has_builtin(__builtin_rotateleft32)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl(x, n);
        }
#   endif
        return Common::LeftCircularShift(x, n);
#endif
    }

    [[nodiscard]] constexpr uint64_t LeftCircularShift(uint64_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateleft64)
        return __builtin_rotateleft64(x, n);
#else // __has_builtin(__builtin_rotateleft64)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl64(x, n);
        }
#   endif
        return Common::LeftCircularShift(x, n);
#endif
    }

#ifdef __SIZEOF_INT128__

    [[nodiscard]] constexpr unsigned __int128 LeftCircularShift(__uint128_t x, unsigned n) noexcept {
        return Common::LeftCircularShift(x, n);
    }

#endif

} // namespace Detail



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T LeftCircularShift(T x, unsigned n) noexcept {
        return Detail::LeftCircularShift(static_cast<Trait::MakeUnsigned_T<T>>(x), n);
    }

} // namespace Bit
