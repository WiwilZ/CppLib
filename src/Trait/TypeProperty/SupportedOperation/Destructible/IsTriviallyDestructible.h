//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if __has_builtin(__is_trivially_destructible) || defined(_MSC_VER)

namespace Trait {

    template <typename T>
    constexpr bool IsTriviallyDestructible_V = __is_trivially_destructible(T);

} // namespace Trait

#elif __has_builtin(__has_trivial_destructor)

#include "IsDestructible.h"


namespace Trait {

    template <typename T>
    constexpr bool IsTriviallyDestructible_V = IsDestructible_V<T> && __has_trivial_destructor(T);

} // namespace Trait

#else // !(__has_builtin(__is_trivially_destructible) || defined(_MSC_VER) || __has_builtin(__has_trivial_destructor))

#error "Compiler does not support __is_trivially_destructible or __has_trivial_destructor."

#endif


namespace Trait {

    template <typename T>
    struct IsTriviallyDestructible : BoolConstant<IsTriviallyDestructible_V<T>> {};

} // namespace Trait
