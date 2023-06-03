//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Macro.h"
#include "../../../Constant.h"


#if __has_builtin(__is_trivially_destructible) || defined(_MSC_VER)

template <typename T>
constexpr bool IsTriviallyDestructible_V = __is_trivially_destructible(T);

#elif __has_builtin(__has_trivial_destructor)

#include "IsDestructible.h"


template <typename T>
constexpr bool IsTriviallyDestructible_V = IsDestructible_V<T> && __has_trivial_destructor(T);

#endif


template <typename T>
struct IsTriviallyDestructible : BoolConstant<IsTriviallyDestructible_V<T>> {};

