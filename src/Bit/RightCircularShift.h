//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Concept/UnsignedIntegerType.h"
#include "../Trait/IntegralTrait.h"
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



namespace Detail::Common {
    template <UnsignedIntegerType T>
    [[nodiscard]] constexpr T RightCircularShift(T x, unsigned n) noexcept {
        constexpr int NumBits = IntegralTrait<T>::NumBits;
        n %= NumBits;
        if (n == 0) {
            return x;
        }
        return (x >> n) | (x << (NumBits - n));
    }
}


template <UnsignedIntegerType T>
[[nodiscard]] constexpr T RightCircularShift(T x, unsigned n) noexcept {
    if constexpr (sizeof(T) == 1) {
#if __has_builtin(__builtin_rotateright8)
        return __builtin_rotateright8(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr8(x, n);
        }
        return Detail::Common::RightCircularShift(x, n);
#else
    return Detail::Common::RightCircularShift(x, n);
#endif
    } else if constexpr (sizeof(T) == 2) {
#if __has_builtin(__builtin_rotateright16)
        return __builtin_rotateright16(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr16(x, n);
        }
        return Detail::Common::RightCircularShift(x, n);
#else
        return Detail::Common::RightCircularShift(x, n);
#endif
    } else if constexpr (sizeof(T) == 4) {
#if __has_builtin(__builtin_rotateright32)
        return __builtin_rotateright32(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr(x, n);
        }
        return Detail::Common::RightCircularShift(x, n);
#else
        return Detail::Common::RightCircularShift(x, n);
#endif
    } else if constexpr (sizeof(T) == 8) {
#if __has_builtin(__builtin_rotateright64)
        return __builtin_rotateright64(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotr64(x, n);
        }
        return Detail::Common::RightCircularShift(x, n);
#else
        return Detail::Common::RightCircularShift(x, n);
#endif
    } else {
        static_assert(sizeof(T) == 16, "Unexpected integer size");
#ifdef __SIZEOF_INT128__
        return Detail::Common::RightCircularShift(x, n);
#endif // __SIZEOF_INT128__
    }
}

