//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsTriviallyConstructible.h"
#include "../../../TypeModification/Reference/AddRValueReference.h"
#include "../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsTriviallyMoveConstructible_V = IsTriviallyConstructible_V<T, AddRValueReference_T<T>>;


    template <typename T>
    struct IsTriviallyMoveConstructible : BoolConstant<IsTriviallyMoveConstructible_V<T>> {};
}
