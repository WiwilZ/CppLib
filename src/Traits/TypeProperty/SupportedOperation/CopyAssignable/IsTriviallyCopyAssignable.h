//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Assignable/IsTriviallyAssignable.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsTriviallyCopyAssignable_V = IsTriviallyAssignable_V<AddLValueReference_T<T>, AddLValueReference_T<const T>>;


    template <typename T>
    struct IsTriviallyCopyAssignable : BoolConstant<IsTriviallyCopyAssignable_V<T>> {};
}
