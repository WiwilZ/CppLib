//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Assignable/IsAssignable.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../TypeModification/Reference/AddRValueReference.h"
#include "../../../Constant.h"


template <typename T>
constexpr bool IsMoveAssignable_V = IsAssignable_V<AddLValueReference_T<T>, AddRValueReference_T<T>>;


template <typename T>
struct IsMoveAssignable : BoolConstant<IsMoveAssignable_V<T>> {};

