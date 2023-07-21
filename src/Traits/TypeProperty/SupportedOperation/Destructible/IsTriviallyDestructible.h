//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_trivially_destructible) || defined(_MSC_VER)
namespace traits {
    template <typename T>
    constexpr bool IsTriviallyDestructible_V = __is_trivially_destructible(T);
}
#elif HAS_BUILTIN(__has_trivial_destructor)
#include "IsDestructible.h"


namespace traits {
    template <typename T>
    constexpr bool IsTriviallyDestructible_V = IsDestructible_V<T> && __has_trivial_destructor(T);
}
#else // !(HAS_BUILTIN(__is_trivially_destructible) || defined(_MSC_VER) || HAS_BUILTIN(__has_trivial_destructor))
#error "Compiler does not support __is_trivially_destructible or __has_trivial_destructor."
#endif


namespace traits {
    template <typename T>
    struct IsTriviallyDestructible : BoolConstant<IsTriviallyDestructible_V<T>> {};
}
