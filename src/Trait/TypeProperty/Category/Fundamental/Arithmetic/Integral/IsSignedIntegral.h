//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../../Macro.h"
#include "../../../../../Constant.h"


#if __has_builtin(__is_integral) && __has_builtin(__is_signed)

template <typename T>
constexpr bool IsSignedIntegral_V = __is_integral(T) && __is_signed(T);

#else

#include "../IsIntegral.h"


template <typename T>
constexpr bool IsSignedIntegral_V = IsIntegral_V<T> && static_cast<T>(-1) < static_cast<T>(0);

#endif // __has_builtin(__is_integral) && __has_builtin(__is_signed)


template <typename T>
struct IsSignedIntegral : BoolConstant<IsSignedIntegral_V<T>> {};

