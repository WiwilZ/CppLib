//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../Macro.h"
#include "../../../../Constant.h"


#if __has_builtin(__is_rvalue_reference)

template <typename T>
constexpr bool IsRValueReference_V = __is_rvalue_reference(T);

#else

template <typename T>
constexpr bool IsRValueReference_V = false;

template <typename T>
constexpr bool IsRValueReference_V<T&&> = true;

#endif // __has_builtin(__is_rvalue_reference)


template <typename T>
struct IsRValueReference : BoolConstant<IsRValueReference_V<T>> {};
