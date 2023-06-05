//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if __has_builtin(__is_arithmetic)

template <typename T>
constexpr bool IsArithmetic_V = __is_arithmetic(T);

#else

#include "Arithmetic/IsIntegral.h"
#include "Arithmetic/IsFloatingPoint.h"


template <typename T>
constexpr bool IsArithmetic_V = IsIntegral_V<T> || IsFloatingPoint_V<T>;

#endif // __has_builtin(__is_arithmetic)


template <typename T>
struct IsArithmetic : BoolConstant<IsArithmetic_V<T>> {};
