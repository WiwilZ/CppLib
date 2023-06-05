//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if __has_builtin(__is_assignable) || defined(_MSC_VER)

template <typename T, typename U>
constexpr bool IsAssignable_V = __is_assignable(T, U);

#else

#include "../../../DeclVal.h"


template <typename T, typename U>
constexpr bool IsAssignable_V = requires{ ::DeclVal<T>() = ::DeclVal<U>(); };

#endif // __has_builtin(__is_assignable) || defined(_MSC_VER)


template <typename T, typename U>
struct IsAssignable : BoolConstant<IsAssignable_V<T, U>> {};


