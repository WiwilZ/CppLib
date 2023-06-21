//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Assignable/IsNothrowAssignable.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../TypeModification/Reference/AddRValueReference.h"
#include "../../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsNothrowMoveAssignable_V = IsNothrowAssignable_V<AddLValueReference_T<T>, AddRValueReference_T<T>>;


    template <typename T>
    struct IsNothrowMoveAssignable : BoolConstant<IsNothrowMoveAssignable_V<T>> {};
}
