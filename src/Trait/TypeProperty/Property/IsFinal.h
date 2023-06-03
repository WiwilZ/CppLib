//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"


template <typename T>
constexpr bool IsFinal_V = __is_final(T);


template <typename T>
struct IsFinal : BoolConstant<IsFinal_V<T>> {};

