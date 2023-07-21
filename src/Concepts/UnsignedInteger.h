//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Traits/TypeProperty/Category/Fundamental/Arithmetic/Integral/Integer/IsUnsignedInteger.h"


namespace concepts {
    template <typename T>
    concept UnsignedInteger = traits::IsUnsignedInteger_V<T>;
}
