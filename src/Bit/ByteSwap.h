//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concepts/TriviallyCopyable.h"
#include "../Traits/MakeIntegerType.h"
#include "../Macro.h"

#include <cstdint>



#if defined(_MSC_VER) && !defined(__clang__)
extern "C" {
    unsigned short _byteswap_ushort(unsigned short);
    unsigned long _byteswap_ulong(unsigned long);
    unsigned __int64 _byteswap_uint64(unsigned __int64);
}
#endif



namespace detail {
    namespace common {
        [[nodiscard]] constexpr uint16_t ByteSwap(uint16_t x) noexcept {
            return (x << 8) | (x >> 8);
        }

        [[nodiscard]] constexpr uint32_t ByteSwap(uint32_t x) noexcept {
            x = (x << 16) | (x >> 16);
            x = ((x & 0x00ff00ff) << 8) | ((x >> 8) & 0x00ff00ff);
            return x;
        }

        [[nodiscard]] constexpr uint64_t ByteSwap(uint64_t x) noexcept {
            x = (x << 32) | (x >> 32);
            x = ((x & 0x0000ffff0000ffff) << 16) | ((x >> 16) & 0x0000ffff0000ffff);
            x = ((x & 0x00ff00ff00ff00ff) << 8) | ((x >> 8) & 0x00ff00ff00ff00ff);
            return x;
        }

#ifdef __SIZEOF_INT128__
        [[nodiscard]] constexpr __uint128_t ByteSwap(__uint128_t x) noexcept {
            constexpr __uint128_t C0 = (__uint128_t{0x00000000FFFFFFFF} << 64) | 0x00000000FFFFFFFF;
            constexpr __uint128_t C1 = (__uint128_t{0x0000FFFF0000FFFF} << 64) | 0x0000FFFF0000FFFF;
            constexpr __uint128_t C2 = (__uint128_t{0x00FF00FF00FF00FF} << 64) | 0x00FF00FF00FF00FF;
            x = (x << 64) | (x >> 64);
            x = ((x & C0) << 32) | ((x >> 32) & C0);
            x = ((x & C1) << 16) | ((x >> 16) & C1);
            x = ((x & C2) << 8) | ((x >> 8) & C2);
            return x;
        }
#endif
    } // namespace common



    [[nodiscard]] constexpr uint16_t ByteSwap(uint16_t x) noexcept {
#if HAS_BUILTIN(__builtin_bswap16)
        return __builtin_bswap16(x);
#else // !HAS_BUILTIN(__builtin_bswap16)
#   if defined(_MSC_VER) && !defined(__clang__)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_ushort(x);
        }
#   endif
        return common::ByteSwap(x);
#endif
    }

    [[nodiscard]] constexpr uint32_t ByteSwap(uint32_t x) noexcept {
#if HAS_BUILTIN(__builtin_bswap32)
        return __builtin_bswap32(x);
#else // !HAS_BUILTIN(__builtin_bswap32)
#   if defined(_MSC_VER) && !defined(__clang__)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_ulong(x);
        }
#   endif
        return common::ByteSwap(x);
#endif
    }

    [[nodiscard]] constexpr uint64_t ByteSwap(uint64_t x) noexcept {
#if HAS_BUILTIN(__builtin_bswap64)
        return __builtin_bswap64(x);
#else // !HAS_BUILTIN(__builtin_bswap64)
#   if defined(_MSC_VER) && !defined(__clang__)
        if (!__builtin_is_constant_evaluated()) {
            return _byteswap_uint64(x);
        }
#   endif
        return common::ByteSwap(x);
#endif
    }

#if defined(__SIZEOF_INT128__)
    [[nodiscard]] constexpr __uint128_t ByteSwap(__uint128_t x) noexcept {
#   if HAS_BUILTIN(__builtin_bswap128)
        return __builtin_bswap128(x);
#   elif HAS_BUILTIN(__builtin_bswap64)
        return (__uint128_t{__builtin_bswap64(x)} << 64) | __builtin_bswap64(x >> 64);
#   else // !HAS_BUILTIN(__builtin_bswap128) && !HAS_BUILTIN(__builtin_bswap64)
        return common::ByteSwap(x);
#   endif
    }
#endif // defined(__SIZEOF_INT128__)
} // namespace detail



template <concepts::TriviallyCopyable T>
[[nodiscard]] constexpr T ByteSwap(T x) noexcept {
    if constexpr (sizeof(T) == 1) {
        return x;
    } else {
        return __builtin_bit_cast(T, detail::ByteSwap(__builtin_bit_cast(traits::MakeUInt_T<sizeof(T)>, x)));
    }
}

