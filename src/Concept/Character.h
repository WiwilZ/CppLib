//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/IsCharacter.h"


namespace Concept {

    template <typename T>
    concept Character = Trait::IsCharacter_V<T>;

} // namespace Concept
