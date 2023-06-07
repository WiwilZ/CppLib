//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__is_nothrow_convertible)

namespace Trait {

    template <typename From, typename To>
    constexpr bool IsNothrowConvertible_V = __is_nothrow_convertible(From, To);

} // namespace Trait

#else // !__has_builtin(__is_nothrow_convertible)

#include "IsConvertible.h"
#include "../Category/Fundamental/IsVoid.h"


namespace Trait {

    template <typename From, typename To>
    constexpr bool IsNothrowConvertible_V = IsVoid_V<From> && IsVoid_V<To> || requires{
        requires IsConvertible_V<From, To>;
        requires requires(void f(To) noexcept, From v) { requires noexcept(f(v)); };
    };

} // namespace Trait

#endif


namespace Trait {

    template <typename From, typename To>
    struct IsNothrowConvertible : BoolConstant<IsNothrowConvertible_V<From, To>> {};

} // namespace Trait
