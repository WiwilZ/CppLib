//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Assignable/IsAssignable.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsCopyAssignable_V = IsAssignable_V<AddLValueReference_T<T>, AddLValueReference_T<const T>>;


    template <typename T>
    struct IsCopyAssignable : BoolConstant<IsCopyAssignable_V<T>> {};
}
