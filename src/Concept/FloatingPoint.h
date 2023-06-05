//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/IsFloatingPoint.h"


template <typename T>
concept FloatingPoint = IsFloatingPoint_V<T>;

