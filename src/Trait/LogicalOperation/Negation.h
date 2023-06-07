//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool Negation_V = !T::Value;


    template <typename T>
    struct Negation : BoolConstant<!T::Value> {};

} // namespace Trait

