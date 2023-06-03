//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"


template <typename T>
constexpr bool IsStandardLayout_V = __is_standard_layout(T);


template <typename T>
struct IsStandardLayout : BoolConstant<IsStandardLayout_V<T>> {};

