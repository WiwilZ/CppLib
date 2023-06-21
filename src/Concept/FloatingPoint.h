//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/IsFloatingPoint.h"


namespace Concept {
    template <typename T>
    concept FloatingPoint = Trait::IsFloatingPoint_V<T>;
}
