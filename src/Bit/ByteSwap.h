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



    [[nodiscard]] constexpr uint16_t ByteSwap(uint16_t x) noexcept {
#if __has_builtin(__builtin_bswap16)
        return __builtin_bswap16(x);
#else // !__has_builtin(__builtin_bswap16)
#   if defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_ushort(x);
        }
# endif
        return Common::ByteSwap(x);
#endif
    }

    [[nodiscard]] constexpr uint32_t ByteSwap(uint32_t x) noexcept {
#if __has_builtin(__builtin_bswap32)
        return __builtin_bswap32(x);
#else // !__has_builtin(__builtin_bswap32)
#   if defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_ulong(x);
        }
#   endif
        return Common::ByteSwap(x);
#endif
    }

    [[nodiscard]] constexpr uint64_t ByteSwap(uint64_t x) noexcept {
#if __has_builtin(__builtin_bswap64)
        return __builtin_bswap64(x);
#else // __has_builtin(__builtin_bswap64)
#   if defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_uint64(x);
        }
#   endif
        return Common::ByteSwap(x);
#endif
    }

#ifdef __SIZEOF_INT128__

    [[nodiscard]] constexpr __uint128_t ByteSwap(__uint128_t x) noexcept {
#   if __has_builtin(__builtin_bswap128)
        return __builtin_bswap128(x);
#   elif __has_builtin(__builtin_bswap64)
        return (static_cast<__uint128_t>(__builtin_bswap64(x)) << 64) | __builtin_bswap64(x >> 64);
#   else // !__has_builtin(__builtin_bswap128) && !__has_builtin(__builtin_bswap64)
        return Common::ByteSwap(x);
#   endif
    }

#endif

} // namespace Detail


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T ByteSwap(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return x;
        } else {
            return Detail::ByteSwap(static_cast<Trait::MakeUnsigned_T<T>>(x));
        }
    }

} // namespace Bit
