//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsClass.h"


namespace Concept {
    template <typename T>
    concept Class = Trait::IsClass_V<T>;
}

