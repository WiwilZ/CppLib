//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_fundamental)

template <typename T>
constexpr bool IsFundamental_V = __is_fundamental(T);

#else

#include "Fundamental/IsArithmetic.h"
#include "Fundamental/IsVoid.h"
#include "Fundamental/IsNullPointer.h"


template <typename T>
constexpr bool IsFundamental_V = IsArithmetic_V<T> || IsVoid_V<T> || IsNullPointer_V<T>;

#endif // __has_builtin(__is_fundamental)


template <typename T>
struct IsFundamental : BoolConstant<IsFundamental_V<T>> {};
