//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Traits/TypeProperty/Category/Fundamental/IsArithmetic.h"


namespace concepts {
    template <typename T>
    concept Arithmetic = traits::IsArithmetic_V<T>;
}
