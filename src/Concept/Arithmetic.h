//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/IsIntegral.h"
#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/IsSignedIntegral.h"
#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/IsUnsignedIntegral.h"
#include "../Trait/TypeProperty/Category/Fundamental/Arithmetic/IsFloatingPoint.h"
#include "../Trait/TypeProperty/Category/Fundamental/IsArithmetic.h"


template <typename T>
concept Integral = IsIntegral_V<T>;

template <typename T>
concept SignedIntegral = IsSignedIntegral_V<T>;

template <typename T>
concept UnsignedIntegral = IsUnsignedIntegral_V<T>;

template <typename T>
concept FloatingPoint = IsFloatingPoint_V<T>;

template <typename T>
concept Arithmetic = IsArithmetic_V<T>;
