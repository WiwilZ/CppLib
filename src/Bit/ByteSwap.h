//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concept/IntegerType.h"
#include "../Macro.h"

#include <cstdint>

#ifdef _MSC_VER
extern "C" {
    unsigned short   __cdecl _byteswap_ushort(unsigned short);
    unsigned long    __cdecl _byteswap_ulong(unsigned long);
    unsigned __int64 __cdecl _byteswap_uint64(unsigned __int64);
}
#endif



namespace Detail{
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
#endif // __SIZEOF_INT128__

    } // namespace Common


    [[nodiscard]] constexpr uint16_t ByteSwap(uint16_t x) noexcept {
#if __has_builtin(__builtin_bswap16)
        return __builtin_bswap16(x);
#elif defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_ushort(x);
        }
        return Common::ByteSwap(x);
#else
        return Common::ByteSwap(x);
#endif
    }

    [[nodiscard]] constexpr uint32_t ByteSwap(uint32_t x) noexcept {
#if __has_builtin(__builtin_bswap32)
        return __builtin_bswap32(x);
#elif defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_ulong(x);
        }
        return Common::ByteSwap(x);
#else
        return Common::ByteSwap(x);
#endif
    }

    [[nodiscard]] constexpr uint64_t ByteSwap(uint64_t x) noexcept {
#if __has_builtin(__builtin_bswap64)
        return __builtin_bswap64(x);
#elif defined(_MSC_VER)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_uint64(x);
        }
        return Common::ByteSwap(x);
#else
        return Common::ByteSwap(x);
#endif
    }

#ifdef __SIZEOF_INT128__
    [[nodiscard]] constexpr __uint128_t ByteSwap(__uint128_t x) noexcept {
#   if __has_builtin(__builtin_bswap128)
        return __builtin_bswap128(x);
#   elif __has_builtin(__builtin_bswap64)
        return (static_cast<__uint128_t>(__builtin_bswap64(x)) << 64) | __builtin_bswap64(x >> 64);
#   else
        return Common::ByteSwap(x);
#   endif
    }
#endif // __SIZEOF_INT128__

} // namespace Detail



template <IntegerType T>
[[nodiscard]] constexpr T ByteSwap(T x) noexcept {
    if constexpr (sizeof(T) == 1) {
        return x;
    } else if constexpr (sizeof(T) == 2) {
        return Detail::ByteSwap(static_cast<uint16_t>(x));
    } else if constexpr (sizeof(T) == 4) {
        return Detail::ByteSwap(static_cast<uint32_t>(x));
    } else if constexpr (sizeof(T) == 8) {
        return Detail::ByteSwap(static_cast<uint64_t>(x));
    } else {
        static_assert(sizeof(T) == 16, "Unexpected integer size");
#ifdef __SIZEOF_INT128__
        return Detail::ByteSwap(static_cast<__uint128_t>(x));
#endif // __SIZEOF_INT128__
    }
}

