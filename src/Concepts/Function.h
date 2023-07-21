//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Traits/TypeProperty/Category/Compound/IsFunction.h"


namespace concepts {
    template <typename T>
    concept Function = traits::IsFunction_V<T>;
}

