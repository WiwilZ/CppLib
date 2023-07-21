//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Traits/TypeProperty/Property/IsTriviallyCopyable.h"


namespace concepts {
    template <typename T>
    concept TriviallyCopyable = traits::IsTriviallyCopyable_V<T>;
}

