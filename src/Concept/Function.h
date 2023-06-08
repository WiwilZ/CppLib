//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsFunction.h"


namespace Concept {

    template <typename T>
    concept Function = Trait::IsFunction_V<T>;

} // namespace Concept

