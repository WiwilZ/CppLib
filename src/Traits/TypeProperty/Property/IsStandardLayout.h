//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Concepts/CompleteVoidOrUnboundedArray.h"
#include "../../Constant.h"


namespace traits {
    template <concepts::CompleteVoidOrUnboundedArray T>
    constexpr bool IsStandardLayout_V = __is_standard_layout(T);


    template <concepts::CompleteVoidOrUnboundedArray T>
    struct IsStandardLayout : BoolConstant<IsStandardLayout_V<T>> {};
}
