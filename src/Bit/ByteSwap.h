//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>

#if defined(_MSC_VER) && !defined(__clang__)

extern "C" {
    unsigned short _byteswap_ushort(unsigned short);
    unsigned long _byteswap_ulong(unsigned long);
    unsigned __int64 _byteswap_uint64(unsigned __int64);
}

#endif



namespace Detail {

    namespace Common {

        [[nodiscard]] constexpr uint16_t ByteSwap(uint16_t x) noexcept {
            return (x << 8) | (x >> 8);
        }

        [[nodiscard]] constexpr uint32_t ByteSwap(uint32_t x) noexcept {
            return (x << 24) | ((x & 0xff00) << 8) | ((x >> 8) & 0xff00) | (x >> 24);
        }

        [[nodiscard]] constexpr uint64_t ByteSwap(uint64_t x) noexcept {
            return (x << 56) | ((x & 0xff00) << 40) | ((x & 0xff0000) << 24) | ((x & 0xff000000) << 8) |
                   ((x >> 8) & 0xff000000) | ((x >> 24) & 0xff0000) | ((x >> 40) & 0xff00) | (x >> 56);
        }

#ifdef __SIZEOF_INT128__
        [[nodiscard]] constexpr __uint128_t ByteSwap(__uint128_t x) noexcept {
            return (static_cast<__uint128_t>(ByteSwap(static_cast<uint64_t>(x))) << 64) | ByteSwap(static_cast<uint64_t>(x >> 64));
        }
#endif

    } // namespace Common

} // namespace Detail


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T ByteSwap(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return x;
        } else {
            Trait::MakeUnsigned_T<T> ux = x;
#if defined(__GNUC__) || defined(__clang__)
            if constexpr (sizeof(T) == 2) {
                return __builtin_bswap16(ux);
            } else if constexpr (sizeof(T) == 4) {
                return __builtin_bswap32(ux);
            } else if constexpr (sizeof(T) == 8) {
                return __builtin_bswap64(ux);
            } else {
                static_assert(sizeof(T) == 16, "Unexpected integer size");
#   if __has_builtin(__builtin_bswap128)
                return __builtin_bswap128(ux);
#   else // !__has_builtin(__builtin_bswap128)
                return (static_cast<__uint128_t>(__builtin_bswap64(ux)) << 64) | __builtin_bswap64(ux >> 64);
#   endif
            }
#else // !defined(__GNUC__) && !defined(__clang__)
#   ifdef _MSC_VER
            if (!__builtin_is_constant_evaluated()) {
                if constexpr (sizeof(T) == 4) {
                    return _byteswap_ulong(ux);
                } else {
                    static_assert(sizeof(T) == 8, "Unexpected integer size");
                    return _byteswap_uint64(ux);
                }
            }
#   endif
            return Detail::Common::ByteSwap(ux);
#endif
        }
    }

} // namespace Bit
