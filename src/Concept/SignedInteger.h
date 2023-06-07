//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/Integer/IsSignedInteger.h"


namespace Concept {

    template <typename T>
    concept SignedInteger = Trait::IsSignedInteger_V<T>;

} // namespace Concept
