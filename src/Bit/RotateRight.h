//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/IntegralTrait.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"

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

    template <Concept::UnsignedInteger T>
    [[nodiscard]] constexpr T RotateRight(T x, unsigned n) noexcept {
        constexpr int NumBits = Trait::IntegralTrait<T>::NumBits;
        n %= NumBits;
        if (n == 0) {
            return x;
        }
        return (x >> n) | (x << (NumBits - n));
    }

} // namespace Detail::Common



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T RotateRight(T x, unsigned n) noexcept {
        Trait::MakeUnsigned_T<T> ux = x;
#if defined(__clang__)
        if constexpr (sizeof(T) == 1) {
            return __builtin_rotateright8(ux);
        } else if constexpr (sizeof(T) == 2) {
            return __builtin_rotateright16(ux);
        } else if constexpr (sizeof(T) == 4) {
            return __builtin_rotateright32(ux);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_rotateright64(ux);
        } else {
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            return Detail::Common::RotateRight(x, n);
        }
#else // !defined(__clang__)
#   if defined(__GNUC__)
        if (!__builtin_is_constant_evaluated() && sizeof(T) <= 8) {
            __asm__("ror %%cl, %0" : "+r"(x) : "c"(n));
            return x;
        }
#   elif defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            if constexpr (sizeof(T) == 1) {
                return _rotr8(ux);
            } else if constexpr (sizeof(T) == 2) {
                return _rotr16(ux);
            } else if constexpr (sizeof(T) == 4) {
                return _rotr(ux);
            } else {
                static_assert(sizeof(T) == 8, "Unexpected integer size");
                return _rotr64(ux);
            }
        }
#   endif
        return Detail::Common::RotateRight(x, n);
#endif
    }

} // namespace Bit
