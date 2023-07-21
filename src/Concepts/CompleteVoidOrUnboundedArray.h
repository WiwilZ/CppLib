//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../Traits/TypeProperty/Category/IsCompleteVoidOrUnboundedArray.h"


namespace concepts {
    template <typename T>
    concept CompleteVoidOrUnboundedArray = traits::IsCompleteVoidOrUnboundedArray_V<T>;
}

