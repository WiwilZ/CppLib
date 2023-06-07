//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_volatile)

namespace Trait {

    template <typename T>
    constexpr bool IsVolatile_V = __is_volatile(T);

} // namespace Trait

#else // !__has_builtin(__is_volatile)

namespace Trait {

    template <typename T>
    constexpr bool IsVolatile_V = false;

    template <typename T>
    constexpr bool IsVolatile_V<volatile T> = true;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsVolatile : BoolConstant<IsVolatile_V<T>> {};

} // namespace Trait
