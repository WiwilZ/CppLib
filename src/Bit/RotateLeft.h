//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"

#include <cstdint>
#include <climits>


namespace Detail::Common {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T RotateLeft(T x, unsigned n) noexcept {
        constexpr int NumBits = sizeof(T) * CHAR_BIT;
        n %= NumBits;
        if (n == 0) {
            return x;
        }
        return (x << n) | (static_cast<Trait::MakeUnsigned_T<T>>(x) >> (NumBits - n));
    }

} // namespace Detail::Common



#ifdef _MSC_VER
extern "C" {
    unsigned char _rotl8(unsigned char, unsigned char);
    unsigned short _rotl16(unsigned short, unsigned char);
    unsigned int _rotl(unsigned int, int);
    unsigned __int64 _rotl64(unsigned __int64, int);
}
#endif


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T RotateLeft(T x, unsigned n) noexcept {
#if defined(__clang__)
        if constexpr (sizeof(T) == 1) {
            return __builtin_rotateleft8(x);
        } else if constexpr (sizeof(T) == 2) {
            return __builtin_rotateleft16(x);
        } else if constexpr (sizeof(T) == 4) {
            return __builtin_rotateleft32(x);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_rotateleft64(x);
        } else {
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            return Detail::Common::RotateLeft(x, n);
        }
#else // !defined(__clang__)
#   if defined(__GNUC__)
        if (!__builtin_is_constant_evaluated() && sizeof(T) <= 8) {
            __asm__("rol %%cl, %0" : "+r"(x) : "c"(n));
            return x;
        }
#   elif defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            if constexpr (sizeof(T) == 1) {
                return _rotl8(x);
            } else if constexpr (sizeof(T) == 2) {
                return _rotl16(x);
            } else if constexpr (sizeof(T) == 4) {
                return _rotl(x);
            } else {
                static_assert(sizeof(T) == 8, "Unexpected integer size");
                return _rotl64(x);
            }
        }
#   endif
        return Detail::Common::RotateLeft(x, n);
#endif
    }

} // namespace Bit
