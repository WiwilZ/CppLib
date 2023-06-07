//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/IsArithmetic.h"


namespace Concept {

    template <typename T>
    concept Arithmetic =  Trait::IsArithmetic_V<T>;

}  // namespace Concept
