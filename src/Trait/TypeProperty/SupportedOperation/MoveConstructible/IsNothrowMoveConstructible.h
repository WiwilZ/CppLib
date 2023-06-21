//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsNothrowConstructible.h"
#include "../../../TypeModification/Reference/AddRValueReference.h"
#include "../../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsNothrowMoveConstructible_V = IsNothrowConstructible_V<T, AddRValueReference_T<T>>;


    template <typename T>
    struct IsNothrowMoveConstructible : BoolConstant<IsNothrowMoveConstructible_V<T>> {};
}
