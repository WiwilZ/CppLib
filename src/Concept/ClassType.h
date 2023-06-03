//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsClass.h"


template <typename T>
concept ClassType = IsClass_V<T>;
