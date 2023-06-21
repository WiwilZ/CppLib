//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Property/IsTriviallyCopyable.h"


namespace Concept {
    template <typename T>
    concept TriviallyCopyable = Trait::IsTriviallyCopyable_V<T>;
}

