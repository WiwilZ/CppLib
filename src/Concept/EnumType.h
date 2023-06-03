//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Trait/TypeProperty/Category/Compound/IsEnum.h"


template <typename T>
concept EnumType = IsEnum_V<T>;

