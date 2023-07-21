//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsEmpty_V = __is_empty(T);


    template <typename T>
    struct IsEmpty : BoolConstant<IsEmpty_V<T>> {};
}
