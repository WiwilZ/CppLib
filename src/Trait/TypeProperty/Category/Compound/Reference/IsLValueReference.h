//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../Macro.h"
#include "../../../../Constant.h"


#if __has_builtin(__is_lvalue_reference)

template <typename T>
constexpr bool IsLValueReference_V = __is_lvalue_reference(T);

#else

template <typename T>
constexpr bool IsLValueReference_V = false;

template <typename T>
constexpr bool IsLValueReference_V<T&> = true;

#endif // __has_builtin(__is_lvalue_reference)


template <typename T>
struct IsLValueReference : BoolConstant<IsLValueReference_V<T>> {};
