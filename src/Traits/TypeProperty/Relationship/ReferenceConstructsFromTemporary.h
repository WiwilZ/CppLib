//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../../Concepts/CompleteVoidOrUnboundedArray.h"
#include "../../Constant.h"


#if HAS_BUILTIN(__reference_constructs_from_temporary)
namespace traits {
    template <concepts::CompleteVoidOrUnboundedArray T1, concepts::CompleteVoidOrUnboundedArray T2>
    constexpr bool ReferenceConstructsFromTemporary_V = __reference_constructs_from_temporary(T1, T2);


    template <concepts::CompleteVoidOrUnboundedArray T1, concepts::CompleteVoidOrUnboundedArray T2>
    struct ReferenceConstructsFromTemporary : BoolConstant<ReferenceConstructsFromTemporary_V<T1, T2>> {};
}
#endif