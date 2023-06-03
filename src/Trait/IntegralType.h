//
// Created by WiwilZ on 2023/5/29.
//

#pragma once


#include <cstdint>


namespace Detail {
    template <int NumBits>
    struct IntegralType;

    template <>
    struct IntegralType<8> {
        using SignedType = int8_t;
        using UnsignedType = uint8_t;
    };

    template <>
    struct IntegralType<16> {
        using SignedType = int16_t;
        using UnsignedType = uint16_t;
    };

    template <>
    struct IntegralType<32> {
        using SignedType = int32_t;
        using UnsignedType = uint32_t;
    };

    template <>
    struct IntegralType<64> {
        using SignedType = int64_t;
        using UnsignedType = uint64_t;
    };

#ifdef __SIZEOF_INT128__
    template <>
    struct IntegralType<128> {
        using SignedType = __int128_t;
        using UnsignedType = __uint128_t;
    };
#endif
}


template <int NumBits>
using SignedIntegral_T = typename Detail::IntegralType<NumBits>::SignedType;

template <int NumBits>
using UnsignedIntegral_T = typename Detail::IntegralType<NumBits>::UnsignedType;
