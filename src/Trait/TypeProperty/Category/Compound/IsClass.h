//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"


template <typename T>
constexpr bool IsClass_V = __is_class(T);


template <typename T>
struct IsClass : BoolConstant<IsClass_V<T>> {};
