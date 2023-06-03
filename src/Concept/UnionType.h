//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsUnion.h"


template <typename T>
concept UnionType = IsUnion_V<T>;
