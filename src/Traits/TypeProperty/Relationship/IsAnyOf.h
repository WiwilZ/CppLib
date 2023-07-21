//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "IsSame.h"
#include "../../Constant.h"


namespace traits {
    template <typename T, typename... Ts>
    constexpr bool IsAnyOf_V = (... || IsSame_V<T, Ts>);


    template <typename T, typename... Ts>
    struct IsAnyOf : BoolConstant<IsAnyOf_V<T, Ts...>> {};
}

