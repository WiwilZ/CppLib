//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


#if HAS_BUILTIN(__is_layout_compatible) || defined(_MSC_VER) && !defined(__clang__)
namespace Trait {
    template <typename T1, typename T2>
    constexpr bool IsLayoutCompatible_V = __is_layout_compatible(T1, T2);


    template <typename T1, typename T2>
    struct IsLayoutCompatible : BoolConstant<IsLayoutCompatible_V<T1, T2>> {};
}
#endif

