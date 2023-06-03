//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsTriviallyConstructible.h"
#include "../../../TypeModification/Reference/AddLValueReference.h"
#include "../../../Constant.h"


template <typename T>
constexpr bool IsTriviallyCopyConstructible_V = IsTriviallyConstructible_V<T, AddLValueReference_T<const T>>;


template <typename T>
struct IsTriviallyCopyConstructible : BoolConstant<IsTriviallyCopyConstructible_V<T>> {};

