//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Concept/CompleteVoidOrUnboundedArray.h"
#include "../../Constant.h"


namespace Trait {
    template <Concept::CompleteVoidOrUnboundedArray T>
    constexpr bool IsStandardLayout_V = __is_standard_layout(T);


    template <Concept::CompleteVoidOrUnboundedArray T>
    struct IsStandardLayout : BoolConstant<IsStandardLayout_V<T>> {};
}
