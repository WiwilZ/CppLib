//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__is_nothrow_convertible)

template <typename From, typename To>
constexpr bool IsNothrowConvertible_V = __is_nothrow_convertible(From, To);

#else

#include "IsConvertible.h"
#include "../Category/Fundamental/IsVoid.h"


template <typename From, typename To>
constexpr bool IsNothrowConvertible_V = IsVoid_V<From> && IsVoid_V<To> || requires{
        requires IsConvertible_V<From, To>;
        requires requires(void f(To) noexcept, From v) { requires noexcept(f(v)); };
};

#endif // __has_builtin(__is_nothrow_convertible)


template <typename From, typename To>
struct IsNothrowConvertible : BoolConstant<IsNothrowConvertible_V<From, To>> {};

