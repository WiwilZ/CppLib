//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Constant.h"


namespace Trait {

    template <typename... Ts>
    constexpr bool Conjunction_V = (... && Ts::Value);


    template <typename... Ts>
    struct Conjunction : BoolConstant<Conjunction_V<Ts...>> {};

} // namespace Trait

