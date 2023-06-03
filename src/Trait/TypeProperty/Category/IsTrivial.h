//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_trivial)

template <typename T>
constexpr bool IsTrivial_V = __is_trivial(T);

#else

template <typename T>
constexpr bool IsTrivial_V = __is_trivially_constructible(T) && __is_trivially_copyable(T);

#endif // __has_builtin(__is_trivial)


template <typename T>
struct IsTrivial : BoolConstant<IsTrivial_V<T>> {};

