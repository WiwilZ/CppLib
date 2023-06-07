//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


namespace Trait {

    template <typename T, typename... Args>
    constexpr bool IsConstructible_V = __is_constructible(T, Args...);

    template <typename T, typename... Args>
    struct IsConstructible : BoolConstant<IsConstructible_V<T, Args...>> {};

} // namespace Trait
