//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_volatile)
namespace traits {
    template <typename T>
    constexpr bool IsVolatile_V = __is_volatile(T);
}
#else // !HAS_BUILTIN(__is_volatile)
namespace traits {
    template <typename T>
    constexpr bool IsVolatile_V = false;

    template <typename T>
    constexpr bool IsVolatile_V<volatile T> = true;
}
#endif


namespace traits {
    template <typename T>
    struct IsVolatile : BoolConstant<IsVolatile_V<T>> {};
}
