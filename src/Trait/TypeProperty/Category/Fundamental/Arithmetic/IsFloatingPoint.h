//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if __has_builtin(__is_floating_point)

template <typename T>
constexpr bool IsFloatingPoint_V = __is_floating_point(T);

#else

#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../Relationship/IsAnyOf.h"


template <typename T>
constexpr bool IsFloatingPoint_V = IsAnyOf_V<RemoveCV_T<T>, float, double, long double>;

#endif // __has_builtin(__is_floating_point)


template <typename T>
struct IsFloatingPoint : BoolConstant<IsFloatingPoint_V<T>> {};
