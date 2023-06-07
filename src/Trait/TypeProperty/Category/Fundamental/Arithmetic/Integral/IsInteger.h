//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "Integer/IsSignedInteger.h"
#include "Integer/IsUnsignedInteger.h"
#include "../../../../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsInteger_V = IsSignedInteger_V<T> || IsUnsignedInteger_V<T>;


    template <typename T>
    struct IsInteger : BoolConstant<IsInteger_V<T>> {};
}
