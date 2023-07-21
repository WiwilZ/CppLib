//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Traits/TypeProperty/Category/Compound/IsEnum.h"


namespace concepts {
    template <typename T>
    concept Enum = traits::IsEnum_V<T>;
}

