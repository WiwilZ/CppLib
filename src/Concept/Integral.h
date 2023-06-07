//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/IsIntegral.h"


namespace Concept {

    template <typename T>
    concept Integral = Trait::IsIntegral_V<T>;

} // namespace Concept
