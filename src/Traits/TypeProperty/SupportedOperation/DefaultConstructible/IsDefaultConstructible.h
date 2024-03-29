//
// Created by WiwilZ on 2023/5/31.
//

#pragma once


#include "../Constructible/IsConstructible.h"
#include "../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsDefaultConstructible_V = IsConstructible_V<T>;


    template <typename T>
    struct IsDefaultConstructible : BoolConstant<IsDefaultConstructible_V<T>> {};
}
