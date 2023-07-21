//
// Created by WiwilZ on 2023/5/29.
//

#pragma once


#include <cstdint>


namespace traits {
    namespace Detail {
        template <int NumBytes>
        struct MakeIntegerType;

        template <>
        struct MakeIntegerType<1> {
            using SignedType = int8_t;
            using UnsignedType = uint8_t;
        };

        template <>
        struct MakeIntegerType<2> {
            using SignedType = int16_t;
            using UnsignedType = uint16_t;
        };

        template <>
        struct MakeIntegerType<4> {
            using SignedType = int32_t;
            using UnsignedType = uint32_t;
        };

        template <>
        struct MakeIntegerType<8> {
            using SignedType = int64_t;
            using UnsignedType = uint64_t;
        };

#ifdef __SIZEOF_INT128__
        template <>
        struct MakeIntegerType<16> {
            using SignedType = __int128_t;
            using UnsignedType = __uint128_t;
        };
#endif
    }


    template <int NumBytes>
    using MakeInt_T = typename Detail::MakeIntegerType<NumBytes>::SignedType;

    template <int NumBytes>
    using MakeUInt_T = typename Detail::MakeIntegerType<NumBytes>::UnsignedType;
}

