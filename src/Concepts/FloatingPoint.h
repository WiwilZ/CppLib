//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Traits/TypeProperty/Category/Fundamental/Arithmetic/IsFloatingPoint.h"


namespace concepts {
    template <typename T>
    concept FloatingPoint = traits::IsFloatingPoint_V<T>;
}
