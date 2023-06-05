//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if __has_builtin(__is_reference)

template <typename T>
constexpr bool IsReference_V = __is_reference(T);

#else

template <typename T>
constexpr bool IsReference_V = false;

template <typename T>
constexpr bool IsReference_V<T&> = true;

template <typename T>
constexpr bool IsReference_V<T&&> = true;

#endif // __has_builtin(__is_reference)


template <typename T>
struct IsReference : BoolConstant<IsReference_V<T>> {};

