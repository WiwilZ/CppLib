//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


namespace traits {

    template <bool Condition, typename If, typename Else>
    struct Conditional {
        using Type = If;
    };

    template <typename If, typename Else>
    struct Conditional<false, If, Else> {
        using Type = Else;
    };


    template <bool Condition, typename If, typename Else>
    using Conditional_T = typename Conditional<Condition, If, Else>::Type;

} // namespace traits

