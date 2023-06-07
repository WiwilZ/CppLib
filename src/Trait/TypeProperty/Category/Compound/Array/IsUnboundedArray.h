//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../../../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool IsUnboundedArray_V = false;

    template <typename T>
    constexpr bool IsUnboundedArray_V<T[]> = true;


    template <typename T>
    struct IsUnboundedArray : BoolConstant<IsUnboundedArray_V<T>> {};

} // namespace Trait

