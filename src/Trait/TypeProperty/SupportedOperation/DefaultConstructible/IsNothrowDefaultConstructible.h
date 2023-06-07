//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsNothrowConstructible.h"
#include "../../../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool IsNothrowDefaultConstructible_V = IsNothrowConstructible_V<T>;


    template <typename T>
    struct IsNothrowDefaultConstructible : BoolConstant<IsNothrowDefaultConstructible_V<T>> {};

} // namespace Trait
