//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsNothrowConstructible.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsNothrowCopyConstructible_V = IsNothrowConstructible_V<T, AddLValueReference_T<const T>>;


    template <typename T>
    struct IsNothrowCopyConstructible : BoolConstant<IsNothrowCopyConstructible_V<T>> {};
}
