//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/IsArithmetic.h"


template <typename T>
concept Arithmetic = IsArithmetic_V<T>;
