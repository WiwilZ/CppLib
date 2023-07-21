//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Traits/TypeProperty/Category/Fundamental/Arithmetic/Integral/IsCharacter.h"


namespace concepts {
    template <typename T>
    concept Character = traits::IsCharacter_V<T>;
}
