//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Traits/TypeProperty/Category/Compound/IsUnion.h"


namespace concepts {
    template <typename T>
    concept Union = traits::IsUnion_V<T>;
}

