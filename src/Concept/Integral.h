//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/IsIntegral.h"


template <typename T>
concept Integral = IsIntegral_V<T>;
