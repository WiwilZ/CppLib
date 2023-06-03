//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_const)

template <typename T>
constexpr bool IsConst_V = __is_const(T);

#else

template <typename T>
constexpr bool IsConst_V = false;

template <typename T>
constexpr bool IsConst_V<const T> = true;

#endif // __has_builtin(__is_const)


template <typename T>
struct IsConst : BoolConstant<IsConst_V<T>> {};
