//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Traits/TypeProperty/Category/Fundamental/Arithmetic/IsIntegral.h"


namespace concepts {
    template <typename T>
    concept Integral = traits::IsIntegral_V<T>;
}
