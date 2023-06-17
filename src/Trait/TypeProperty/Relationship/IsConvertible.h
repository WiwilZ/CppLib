//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"


#if HAS_BUILTIN(__is_convertible)

namespace Trait {

    template <typename From, typename To>
    constexpr bool IsConvertible_V = __is_convertible(From, To);

} // namespace Trait

#elif HAS_BUILTIN(__is_convertible_to) || defined(_MSC_VER)

namespace Trait {

    template <typename From, typename To>
    constexpr bool IsConvertible_V = __is_convertible_to(From, To);

} // namespace Trait

#else // !(HAS_BUILTIN(__is_convertible) || HAS_BUILTIN(__is_convertible_to) || defined(_MSC_VER))

#include "../Category/Fundamental/IsVoid.h"
#include "../Category/Compound/IsFunction.h"
#include "../Category/Compound/IsArray.h"


namespace Trait {

    template <typename From, typename To>
    constexpr bool IsConvertible_V = IsVoid_V<From> && IsVoid_V<To> || requires {
        requires !IsVoid_V<To> && !IsFunction_V<To> && !IsArray_V<To>;
        requires requires(void f(To), From v) { f(v); };
    };

} // namespace Trait

#endif


namespace Trait {

    template <typename From, typename To>
    struct IsConvertible : BoolConstant<IsConvertible_V<From, To>> {};

} // namespace Trait

