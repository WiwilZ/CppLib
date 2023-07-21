//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsConstructible.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsCopyConstructible_V = IsConstructible_V<T, AddLValueReference_T<const T>>;


    template <typename T>
    struct IsCopyConstructible : BoolConstant<IsCopyConstructible_V<T>> {};
}
