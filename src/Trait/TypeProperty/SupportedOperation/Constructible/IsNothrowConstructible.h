//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_nothrow_constructible) || defined(_MSC_VER)

namespace Trait {

    template <typename T, typename... Args>
    constexpr bool IsNothrowConstructible_V = __is_nothrow_constructible(T, Args...);

} // namespace Trait

#else // !(HAS_BUILTIN(__is_nothrow_constructible) || defined(_MSC_VER))

#include "IsConstructible.h"
#include "../../../DeclVal.h"
#include "../../../TypeProperty/Category/Compound/IsReference.h"

#include <cstddef>


namespace Trait {

    namespace Detail {

        template <bool IsConstructible_/*false*/, bool IsReference_, typename T, typename... Args>
        constexpr bool IsNothrowConstructible_V = false;

        template <typename T, typename... Args>
        constexpr bool IsNothrowConstructible_V<true, false, T, Args...> = noexcept(T(Trait::DeclVal<Args>()...));

        template <typename T, typename Arg>
        constexpr bool IsNothrowConstructible_V<true, true, T, Arg> = requires(void f(T) noexcept, Arg v) { requires noexcept(f(v)); };

    } // namespace Detail


    template <typename T, typename... Args>
    constexpr bool IsNothrowConstructible_V = Detail::IsNothrowConstructible_V<IsConstructible_V<T, Args...>, IsReference_V<T>, T, Args...>;

    template <typename T, std::size_t N>
    constexpr bool IsNothrowConstructible_V<T[N]> = Detail::IsNothrowConstructible_V<IsConstructible_V<T>, IsReference_V<T>, T>;

} // namespace Trait

#endif


namespace Trait {

    template <typename T, typename... Args>
    struct IsNothrowConstructible : BoolConstant<IsNothrowConstructible_V<T, Args...>> {};

} // namespace Trait
