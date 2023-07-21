//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Constant.h"


namespace traits {
    template <typename... Ts>
    constexpr bool Disjunction_V = (... || Ts::Value);


    template <typename... Ts>
    struct Disjunction : BoolConstant<Disjunction_V<Ts...>> {};
}

