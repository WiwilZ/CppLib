//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../ArithmeticType.h"


namespace traits {
    template <typename T, T Val>
    struct Constant {
        using Type = Constant;
        using ValueType = T;
        static constexpr ValueType Value = Val;

        constexpr operator ValueType() const noexcept { return Val; }

        constexpr ValueType operator()() const noexcept { return Val; }
    };


    template <usize Val>
    using SizeConstant = Constant<usize, Val>;

    template <bool Val>
    using BoolConstant = Constant<bool, Val>;


    using TrueType = BoolConstant<true>;
    using FalseType = BoolConstant<false>;
}

