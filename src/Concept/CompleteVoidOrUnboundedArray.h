//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../Trait/TypeProperty/Category/IsCompleteVoidOrUnboundedArray.h"


namespace Concept {
    template <typename T>
    concept CompleteVoidOrUnboundedArray = Trait::IsCompleteVoidOrUnboundedArray_V<T>;
}

