//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsConstructible.h"
#include "../../../TypeModification/Reference/AddRValueReference.h"
#include "../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsMoveConstructible_V = IsConstructible_V<T, AddRValueReference_T<T>>;


    template <typename T>
    struct IsMoveConstructible : BoolConstant<IsMoveConstructible_V<T>> {};
}
