//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Traits/TypeProperty/Category/Compound/IsClass.h"


namespace concepts {
    template <typename T>
    concept Class = traits::IsClass_V<T>;
}

