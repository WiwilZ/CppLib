//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsUnion.h"


namespace Concept {
    template <typename T>
    concept Union = Trait::IsUnion_V<T>;
}

