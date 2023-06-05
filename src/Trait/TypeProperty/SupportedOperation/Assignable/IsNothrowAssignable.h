//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if __has_builtin(__is_nothrow_assignable) || defined(_MSC_VER)

template <typename T, typename U>
constexpr bool IsNothrowAssignable_V = __is_nothrow_assignable(T, U);

#else

#include "../../../DeclVal.h"

template <typename T, typename U>
constexpr bool IsNothrowAssignable_V = requires{
    requires noexcept(::DeclVal<T>() = ::DeclVal<U>());
};

#endif // __has_builtin(__is_nothrow_assignable) || defined(_MSC_VER)


template <typename T, typename U>
struct IsNothrowAssignable : BoolConstant<IsNothrowAssignable_V<T, U>> {};
