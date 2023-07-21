//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"


#if HAS_BUILTIN(__is_nothrow_convertible)
namespace traits {
    template <typename From, typename To>
    constexpr bool IsNothrowConvertible_V = __is_nothrow_convertible(From, To);
}
#else // !HAS_BUILTIN(__is_nothrow_convertible)
#include "IsConvertible.h"
#include "../Category/Fundamental/IsVoid.h"


namespace traits {
    template <typename From, typename To>
    constexpr bool IsNothrowConvertible_V = IsVoid_V<From> && IsVoid_V<To> || requires {
        requires IsConvertible_V<From, To>;
        requires requires(void f(To) noexcept, From v) { requires noexcept(f(v)); };
    };
}
#endif


namespace traits {
    template <typename From, typename To>
    struct IsNothrowConvertible : BoolConstant<IsNothrowConvertible_V<From, To>> {};
}
