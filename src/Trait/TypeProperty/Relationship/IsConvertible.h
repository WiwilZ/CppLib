//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__is_convertible)

template <typename From, typename To>
constexpr bool IsConvertible_V = __is_convertible(From, To);

#elif __has_builtin(__is_convertible_to) || defined(_MSC_VER)

template <typename From, typename To>
constexpr bool IsConvertible_V = __is_convertible_to(From, To);

#else

#include "../Category/Fundamental/IsVoid.h"
#include "../Category/Compound/IsFunction.h"
#include "../Category/Compound/IsArray.h"


template <typename From, typename To>
constexpr bool IsConvertible_V = IsVoid_V<From> && IsVoid_V<To> || requires{
    requires !IsVoid_V<To> && !IsFunction_V<To> && !IsArray_V<To>;
    requires requires(void f(To), From v) { f(v); };
};

#endif // __has_builtin(__is_convertible) || __has_builtin(__is_convertible_to) || defined(_MSC_VER)


template <typename From, typename To>
struct IsConvertible : BoolConstant<IsConvertible_V<From, To>> {};
