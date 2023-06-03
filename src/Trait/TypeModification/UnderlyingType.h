//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../Concept/EnumType.h"


template <EnumType T>
struct UnderlyingType {
    using Type = __underlying_type(T);
};


template <EnumType T>
using UnderlyingType_T = typename UnderlyingType<T>::Type;
