//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Traits/TypeProperty/Category/Fundamental/Arithmetic/Integral/Integer/IsSignedInteger.h"


namespace concepts {
    template <typename T>
    concept SignedInteger = traits::IsSignedInteger_V<T>;
}
