//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


template <typename T, typename... Args>
constexpr bool IsTriviallyConstructible_V = __is_trivially_constructible(T, Args...);


template <typename T, typename... Args>
struct IsTriviallyConstructible : BoolConstant<IsTriviallyConstructible_V<T, Args...>> {};

