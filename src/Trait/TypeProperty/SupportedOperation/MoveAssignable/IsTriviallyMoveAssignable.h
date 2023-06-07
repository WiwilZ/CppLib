//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Assignable/IsTriviallyAssignable.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../TypeModification/Reference/AddRValueReference.h"
#include "../../../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool IsTriviallyMoveAssignable_V = IsTriviallyAssignable_V<AddLValueReference_T<T>, AddRValueReference_T<T>>;


    template <typename T>
    struct IsTriviallyMoveAssignable : BoolConstant<IsTriviallyMoveAssignable_V<T>> {};

} // namespace Trait
