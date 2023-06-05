//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if __has_builtin(__is_nothrow_constructible) || defined(_MSC_VER)

template <typename T, typename... Args>
constexpr bool IsNothrowConstructible_V = __is_nothrow_constructible(T, Args...);

#else

#include <cstddef>
#include "IsConstructible.h"
#include "../../../DeclVal.h"
#include "../../../TypeProperty/Category/Compound/IsReference.h"


namespace Detail {
    template <bool IsConstructible_/*false*/, bool IsReference_, typename T, typename... Args>
    constexpr bool IsNothrowConstructible_V = false;

    template <typename T, typename... Args>
    constexpr bool IsNothrowConstructible_V<true, false, T, Args...> = noexcept(T(::DeclVal<Args>()...));

    template <typename T, typename Arg>
    constexpr bool IsNothrowConstructible_V<true, true, T, Arg> = requires(void f(T) noexcept, Arg v) { requires noexcept(f(v)); };
}

template <typename T, typename... Args>
constexpr bool IsNothrowConstructible_V = Detail::IsNothrowConstructible_V<IsConstructible_V<T, Args...>, IsReference_V<T>, T, Args...>;

template <typename T, std::size_t N>
constexpr bool IsNothrowConstructible_V<T[N]> = Detail::IsNothrowConstructible_V<IsConstructible_V<T>, IsReference_V<T>, T>;

#endif // __has_builtin(__is_nothrow_constructible) || defined(_MSC_VER)


template <typename T, typename... Args>
struct IsNothrowConstructible : BoolConstant<IsNothrowConstructible_V<T, Args...>> {};
