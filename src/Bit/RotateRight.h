//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"

#include <cstdint>
#include <climits>



#ifdef _MSC_VER
extern "C" {
    unsigned char _rotr8(unsigned char, unsigned char);
    unsigned short _rotr16(unsigned short, unsigned char);
    unsigned int _rotr(unsigned int, int);
    unsigned __int64 _rotr64(unsigned __int64, int);
}
#endif



namespace Detail::Common {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T RotateRight(T x, unsigned n) noexcept {
        constexpr int NumBits = sizeof(T) * CHAR_BIT;
        n %= NumBits;
        if (n == 0) {
            return x;
        }
        return (static_cast<Trait::MakeUnsigned_T<T>>(x) >> n) | (x << (NumBits - n));
    }

} // namespace Detail::Common



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T RotateRight(T x, unsigned n) noexcept {
#if defined(__clang__)
        if constexpr (sizeof(T) == 1) {
            return __builtin_rotateright8(x);
        } else if constexpr (sizeof(T) == 2) {
            return __builtin_rotateright16(x);
        } else if constexpr (sizeof(T) == 4) {
            return __builtin_rotateright32(x);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_rotateright64(x);
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
                return _rotr8(x);
            } else if constexpr (sizeof(T) == 2) {
                return _rotr16(x);
            } else if constexpr (sizeof(T) == 4) {
                return _rotr(x);
            } else {
                static_assert(sizeof(T) == 8, "Unexpected integer size");
                return _rotr64(x);
            }
        }
#   endif
        return Detail::Common::RotateRight(x, n);
#endif
    }

} // namespace Bit
