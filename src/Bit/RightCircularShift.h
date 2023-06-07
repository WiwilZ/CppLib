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
    unsigned char _rotr8(unsigned char, unsigned char);
    unsigned short _rotr16(unsigned short, unsigned char);
    unsigned int _rotr(unsigned int, int);
    unsigned __int64 _rotr64(unsigned __int64, int);
}

#endif



namespace Detail {

    namespace Common {

        template <Concept::UnsignedInteger T>
        [[nodiscard]] constexpr T RightCircularShift(T x, unsigned n) noexcept {
            constexpr int NumBits = Trait::IntegralTrait<T>::NumBits;
            n %= NumBits;
            if (n == 0) {
                return x;
            }
            return (x >> n) | (x << (NumBits - n));
        }

    } // namespace Common



    [[nodiscard]] constexpr uint8_t RightCircularShift(uint8_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateright8)
        return __builtin_rotateright8(x, n);
#else // __has_builtin(__builtin_rotateright8)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr8(x, n);
        }
#   endif
        return Common::RightCircularShift(x, n);
#endif
    }

    [[nodiscard]] constexpr uint16_t RightCircularShift(uint16_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateright16)
        return __builtin_rotateright16(x, n);
#else // __has_builtin(__builtin_rotateright16)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr16(x, n);
        }
#   endif
        return Common::RightCircularShift(x, n);
#endif
    }

    [[nodiscard]] constexpr uint32_t RightCircularShift(uint32_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateright32)
        return __builtin_rotateright32(x, n);
#else // __has_builtin(__builtin_rotateright32)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr(x, n);
        }
#   endif
        return Common::RightCircularShift(x, n);
#endif
    }

    [[nodiscard]] constexpr uint64_t RightCircularShift(uint64_t x, unsigned n) noexcept {
#if __has_builtin(__builtin_rotateright64)
        return __builtin_rotateright64(x, n);
#else // __has_builtin(__builtin_rotateright64)
#   if defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr64(x, n);
        }
#   endif
        return Common::RightCircularShift(x, n);
#endif
    }

#ifdef __SIZEOF_INT128__

    [[nodiscard]] constexpr unsigned __int128 RightCircularShift(__uint128_t x, unsigned n) noexcept {
        return Common::RightCircularShift(x, n);
    }

#endif

} // namespace Detail



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T RightCircularShift(T x, unsigned n) noexcept {
        return Detail::RightCircularShift(static_cast<Trait::MakeUnsigned_T<T>>(x), n);
    }

} // namespace Bit
