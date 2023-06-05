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
    unsigned char _rotl8(unsigned char, unsigned char);
    unsigned short _rotl16(unsigned short, unsigned char);
    unsigned int _rotl(unsigned int, int);
    unsigned __int64 _rotl64(unsigned __int64, int);
}
#endif



namespace Detail::Common {
    template <UnsignedIntegerType T>
    [[nodiscard]] constexpr T LeftCircularShift(T x, unsigned n) noexcept {
        constexpr int NumBits = IntegralTrait<T>::NumBits;
        n %= NumBits;
        if (n == 0) {
            return x;
        }
        return (x << n) | (x >> (NumBits - n));
    }
}


template <UnsignedIntegerType T>
[[nodiscard]] constexpr T LeftCircularShift(T x, unsigned n) noexcept {
    if constexpr (sizeof(T) == 1) {
#if __has_builtin(__builtin_rotateleft8)
        return __builtin_rotateleft8(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl8(x, n);
        }
        return Detail::Common::LeftCircularShift(x, n);
#else
    return Detail::Common::LeftCircularShift(x, n);
#endif
    } else if constexpr (sizeof(T) == 2) {
#if __has_builtin(__builtin_rotateleft16)
        return __builtin_rotateleft16(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl16(x, n);
        }
        return Detail::Common::LeftCircularShift(x, n);
#else
        return Detail::Common::LeftCircularShift(x, n);
#endif
    } else if constexpr (sizeof(T) == 4) {
#if __has_builtin(__builtin_rotateleft32)
        return __builtin_rotateleft32(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl(x, n);
        }
        return Detail::Common::LeftCircularShift(x, n);
#else
        return Detail::Common::LeftCircularShift(x, n);
#endif
    } else if constexpr (sizeof(T) == 8) {
#if __has_builtin(__builtin_rotateleft64)
        return __builtin_rotateleft64(x);
#elif defined(_MSC_VER)
        if(!__builtin_is_constant_evaluated()) {
            return _rotl64(x, n);
        }
        return Detail::Common::LeftCircularShift(x, n);
#else
        return Detail::Common::LeftCircularShift(x, n);
#endif
    } else {
        static_assert(sizeof(T) == 16, "Unexpected integer size");
#ifdef __SIZEOF_INT128__
        return Detail::Common::LeftCircularShift(x, n);
#endif // __SIZEOF_INT128__
    }
}

