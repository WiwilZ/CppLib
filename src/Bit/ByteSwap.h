//
// Created by WiwilZ on 2023/6/4.
//

#pragma once

#include "../Concept/Integer.h"
#include "../Concept/UnsignedInteger.h"
#include "../Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "../Macro.h"

#include <cstdint>




#if defined(__GNUC__) || defined(__clang__)

namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T ByteSwap(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return x;
        } else if constexpr (sizeof(T) == 2) {
            return __builtin_bswap16(x);
        } else if constexpr (sizeof(T) == 4) {
            return __builtin_bswap32(x);
        } else if constexpr (sizeof(T) == 8) {
            return __builtin_bswap64(x);
        } else {
            static_assert(sizeof(T) == 16, "Unexpected integer size");
#if __has_builtin(__builtin_bswap128)
            return __builtin_bswap128(x);
#else // !__has_builtin(__builtin_bswap128)
            return (static_cast<__uint128_t>(__builtin_bswap64(x)) << 64) | __builtin_bswap64(static_cast<__uint128_t>(x) >> 64);
# endif
        }
    }

} // namespace Bit

#else // !defined(__GNUC__) && !defined(__clang__)

namespace Detail::Common {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T ByteSwap(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return x;
        } else if constexpr (sizeof(T) == 2) {
            return (x << 8) | (static_cast<uint16_t>(x) >> 8);
        } else if constexpr (sizeof(T) == 4) {
            uint32_t ux = x;
            return (ux << 24) | ((ux & 0xff00) << 8) | ((ux >> 8) & 0xff00) | (ux >> 24);
        } else if constexpr (sizeof(T) == 8) {
            uint64_t ux = x;
            return (ux << 56) | ((ux & 0xff00) << 40) | ((ux & 0xff0000) << 24) | ((ux & 0xff000000) << 8) |
                        ((ux >> 8) & 0xff000000) | ((ux >> 24) & 0xff0000) | ((ux >> 40) & 0xff00) | (ux >> 56);
        } else {
#ifdef __SIZEOF_INT128__
            static_assert(sizeof(T) == 16, "Unexpected integer size");
            return (static_cast<__uint128_t>(ByteSwap(static_cast<uint64_t>(x))) << 64) | ByteSwap(static_cast<uint64_t>(static_cast<__uint128_t>(x) >> 64));
#else
            static_assert(sizeof(T) <= 8, "Unexpected integer size");
#endif
        }
    }

} // namespace Detail::Common


#ifdef _MSC_VER
extern "C" {
    unsigned short _byteswap_ushort(unsigned short);
    unsigned long _byteswap_ulong(unsigned long);
    unsigned __int64 _byteswap_uint64(unsigned __int64);
}
#endif


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T ByteSwap(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return x;
        } else {
#ifdef _MSC_VER
            if (!__builtin_is_constant_evaluated()) {
                if constexpr (sizeof(T) == 2) {
                    return _byteswap_ushort(x);
                } else if constexpr (sizeof(T) == 4) {
                    return _byteswap_ulong(x);
                } else {
                    static_assert(sizeof(T) == 8, "Unexpected integer size");
                    return _byteswap_uint64(x);
                }
            }
#endif
            return Detail::Common::ByteSwap(x);
        }
    }

} // namespace Bit

#endif


