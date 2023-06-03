//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../../Constant.h"


template <typename T>
constexpr bool IsScopedEnum_V = requires{
        requires __is_enum(T);
        sizeof(T);
        requires !requires(void f(int), T v) { f(v); };
};


template <typename T>
struct IsScopedEnum : BoolConstant<IsScopedEnum_V<T>> {};
