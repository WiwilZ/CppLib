//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_const)
namespace traits {
    template <typename T>
    constexpr bool IsConst_V = __is_const(T);
}
#else // !HAS_BUILTIN(__is_const)
namespace traits {
    template <typename T>
    constexpr bool IsConst_V = false;

    template <typename T>
    constexpr bool IsConst_V<const T> = true;
}
#endif


namespace traits {
    template <typename T>
    struct IsConst : BoolConstant<IsConst_V<T>> {};
}

