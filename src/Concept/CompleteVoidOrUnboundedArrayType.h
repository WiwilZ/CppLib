//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../Trait/TypeProperty/Category/IsCompleteVoidOrUnboundedArray.h"


template <typename T>
concept CompleteVoidOrUnboundedArrayType = IsCompleteVoidOrUnboundedArray_V<T>;

