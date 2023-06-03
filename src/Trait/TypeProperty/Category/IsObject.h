//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_object)

template <typename T>
constexpr bool IsObject_V = __is_object(T);

#else

#include "../Property/IsConst.h"
#include "Fundamental/IsVoid.h"


template <typename T>
constexpr bool IsObject_V = IsConst_V<const T> && !IsVoid_V<T>; // `IsConst_V<const T>` excludes function types and reference types

#endif // __has_builtin(__is_object)


template <typename T>
struct IsObject : BoolConstant<IsObject_V<T>> {};
