//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../../Concept/CompleteVoidOrUnboundedArray.h"
#include "../../Constant.h"


#if HAS_BUILTIN(__reference_converts_from_temporary)

namespace Trait {

    template <Concept::CompleteVoidOrUnboundedArray T1, Concept::CompleteVoidOrUnboundedArray T2>
    constexpr bool ReferenceConvertsFromTemporary_V = __reference_converts_from_temporary(T1, T2);


    template <Concept::CompleteVoidOrUnboundedArray T1, Concept::CompleteVoidOrUnboundedArray T2>
    struct ReferenceConvertsFromTemporary : BoolConstant<ReferenceConvertsFromTemporary_V<T1, T2>> {};

}

#endif
