//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_volatile)

template <typename T>
constexpr bool IsVolatile_V = __is_volatile(T);

#else

template <typename T>
constexpr bool IsVolatile_V = false;

template <typename T>
constexpr bool IsVolatile_V<volatile T> = true;

#endif // __has_builtin(__is_volatile)


template <typename T>
struct IsVolatile : BoolConstant<IsVolatile_V<T>> {};
