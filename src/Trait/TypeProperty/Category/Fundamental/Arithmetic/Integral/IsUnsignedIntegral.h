//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../../Macro.h"
#include "../../../../../Constant.h"


#if __has_builtin(__is_integral) && __has_builtin(__is_unsigned)

template <typename T>
constexpr bool IsUnsignedIntegral_V = __is_integral(T) && __is_unsigned(T);

#else

#include "../IsIntegral.h"


template <typename T>
constexpr bool IsUnsignedIntegral_V = IsIntegral_V<T> && static_cast<T>(0) < static_cast<T>(-1);

#endif // __has_builtin(__is_integral) && __has_builtin(__is_unsigned)


template <typename T>
struct IsUnsignedIntegral : BoolConstant<IsUnsignedIntegral_V<T>>{};
