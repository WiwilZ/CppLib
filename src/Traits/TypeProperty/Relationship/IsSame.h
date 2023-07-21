//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_same)
namespace traits {
    template <typename T1, typename T2>
    constexpr bool IsSame_V = __is_same(T1, T2);
}
#else // !HAS_BUILTIN(__is_same)
namespace traits {
    template <typename T1, typename T2>
    constexpr bool IsSame_V = false;

    template <typename T>
    constexpr bool IsSame_V<T, T> = true;
}
#endif


namespace traits {
    template <typename T1, typename T2>
    constexpr bool IsNotSame_V = !IsSame_V<T1, T2>;


    template <typename T1, typename T2>
    struct IsSame : BoolConstant<IsSame_V<T1, T2>> {};

    template <typename T1, typename T2>
    struct IsNotSame : BoolConstant<IsNotSame_V<T1, T2>> {};
}

