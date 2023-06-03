//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_scalar)

template <typename T>
constexpr bool IsScalar_V = __is_scalar(T);

#else

#include "Fundamental/IsArithmetic.h"
#include "Compound/IsPointer.h"
#include "Compound/IsMemberPointer.h"
#include "Compound/IsEnum.h"
#include "Fundamental/IsNullPointer.h"


template <typename T>
constexpr bool IsScalar_V = IsArithmetic_V<T>|| IsPointer_V<T> || IsMemberPointer_V<T> || IsEnum_V<T>  || IsNullPointer_V<T>;

#endif // __has_builtin(__is_scalar)


template <typename T>
struct IsScalar : BoolConstant<IsScalar_V<T>> {};
