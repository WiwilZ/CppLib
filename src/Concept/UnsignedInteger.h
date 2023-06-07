//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/Integer/IsUnsignedInteger.h"


namespace Concept {
    template <typename T>
    concept UnsignedInteger = Trait::IsUnsignedInteger_V<T>;
}
