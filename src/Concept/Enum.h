//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsEnum.h"


namespace Concept {
    template <typename T>
    concept Enum = Trait::IsEnum_V<T>;
}

