//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../Constructible/IsTriviallyConstructible.h"
#include "../../../Constant.h"


template <typename T>
constexpr bool IsTriviallyDefaultConstructible_V = IsTriviallyConstructible_V<T>;


template <typename T>
struct IsTriviallyDefaultConstructible : BoolConstant<IsTriviallyDefaultConstructible_V<T>> {};

