//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include <cstddef>


namespace Trait {

    template <typename T, T Val>
    struct Constant {
        using Type = Constant;
        using ValueType = T;
        static constexpr ValueType Value = Val;

        constexpr operator ValueType() const noexcept { return Val; }

        constexpr ValueType operator()() const noexcept { return Val; }
    };


    template <std::size_t Val>
    using SizeConstant = Constant<std::size_t, Val>;

    template <bool Val>
    using BoolConstant = Constant<bool, Val>;


    using TrueType = BoolConstant<true>;
    using FalseType = BoolConstant<false>;

} // namespace Trait

