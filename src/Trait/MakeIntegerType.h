//
// Created by WiwilZ on 2023/5/29.
//

#pragma once


#include <cstdint>


namespace Detail {
    template <int NumBits>
    struct MakeIntegerType;

    template <>
    struct MakeIntegerType<8> {
        using SignedType = int8_t;
        using UnsignedType = uint8_t;
    };

    template <>
    struct MakeIntegerType<16> {
        using SignedType = int16_t;
        using UnsignedType = uint16_t;
    };

    template <>
    struct MakeIntegerType<32> {
        using SignedType = int32_t;
        using UnsignedType = uint32_t;
    };

    template <>
    struct MakeIntegerType<64> {
        using SignedType = int64_t;
        using UnsignedType = uint64_t;
    };

#ifdef __SIZEOF_INT128__
    template <>
    struct IntegerType<128> {
        using SignedType = __int128_t;
        using UnsignedType = __uint128_t;
    };
#endif
}


template <int NumBits>
using MakeInt_T = typename Detail::MakeIntegerType<NumBits>::SignedType;

template <int NumBits>
using MakeUInt_T = typename Detail::MakeIntegerType<NumBits>::UnsignedType;
