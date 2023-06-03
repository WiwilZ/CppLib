//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"


template <typename T>
constexpr bool IsAggregate_V = __is_aggregate(T);


template <typename T>
struct IsAggregate : BoolConstant<IsAggregate_V<T>> {};
