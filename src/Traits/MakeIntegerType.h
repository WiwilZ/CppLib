//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../ArithmeticType.h"


namespace traits {
    namespace detail {
        template <usize NumBytes>
        struct MakeIntegerType;

        template <>
        struct MakeIntegerType<1> {
            using SignedType = i8;
            using UnsignedType = u8;
        };

        template <>
        struct MakeIntegerType<2> {
            using SignedType = i16;
            using UnsignedType = u16;
        };

        template <>
        struct MakeIntegerType<4> {
            using SignedType = i32;
            using UnsignedType = u32;
        };

        template <>
        struct MakeIntegerType<8> {
            using SignedType = i64;
            using UnsignedType = u64;
        };

#if HAS_INT128
        template <>
        struct MakeIntegerType<16> {
            using SignedType = i128;
            using UnsignedType = u128;
        };
#endif
    }


    template <usize NumBytes>
    using MakeInt_T = typename detail::MakeIntegerType<NumBytes>::SignedType;

    template <usize NumBytes>
    using MakeUInt_T = typename detail::MakeIntegerType<NumBytes>::UnsignedType;
}

