//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Macro.h"
#include "../../../Constant.h"


#if __has_builtin(__is_function)

template <typename T>
constexpr bool IsFunction_V = __is_function(T);

#else

#include "../../Property/IsConst.h"
#include "IsReference.h"


template <typename T>
constexpr bool IsFunction_V = !IsConst_V<const T> && !IsReference_V<T>; // Only function types and reference types can't be const qualified

#endif // __has_builtin(__is_function)


template <typename T>
struct IsFunction : BoolConstant<IsFunction_V<T>> {};
