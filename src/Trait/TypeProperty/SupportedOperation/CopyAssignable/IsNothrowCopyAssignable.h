//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Assignable/IsNothrowAssignable.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsNothrowCopyAssignable_V = IsNothrowAssignable_V<AddLValueReference_T<T>, AddLValueReference_T<const T>>;


    template <typename T>
    struct IsNothrowCopyAssignable : BoolConstant<IsNothrowCopyAssignable_V<T>> {};
}
