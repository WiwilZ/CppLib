//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_nothrow_constructible) || defined(_MSC_VER)
namespace traits {
    template <typename T, typename... Args>
    constexpr bool IsNothrowConstructible_V = __is_nothrow_constructible(T, Args...);
}
#else // !(HAS_BUILTIN(__is_nothrow_constructible) || defined(_MSC_VER))
#include "IsConstructible.h"
#include "../../../DeclVal.h"
#include "../../../TypeProperty/Category/Compound/IsReference.h"

#include <cstddef>


namespace traits {
    namespace detail {
        template <bool IsConstructible_/*false*/, bool IsReference_, typename T, typename... Args>
        constexpr bool IsNothrowConstructible_V = false;

        template <typename T, typename... Args>
        constexpr bool IsNothrowConstructible_V<true, false, T, Args...> = noexcept(T(traits::DeclVal<Args>()...));

        template <typename T, typename Arg>
        constexpr bool IsNothrowConstructible_V<true, true, T, Arg> = requires(void f(T) noexcept, Arg v) { requires noexcept(f(v)); };
    }

    template <typename T, typename... Args>
    constexpr bool IsNothrowConstructible_V = detail::IsNothrowConstructible_V<IsConstructible_V<T, Args...>, IsReference_V<T>, T, Args...>;

    template <typename T, std::size_t N>
    constexpr bool IsNothrowConstructible_V<T[N]> = detail::IsNothrowConstructible_V<IsConstructible_V<T>, IsReference_V<T>, T>;
}
#endif


namespace traits {
    template <typename T, typename... Args>
    struct IsNothrowConstructible : BoolConstant<IsNothrowConstructible_V<T, Args...>> {};
}
