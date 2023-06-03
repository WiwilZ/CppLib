//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


template <typename T>
constexpr bool HasVirtualDestructor_V = __has_virtual_destructor(T);


template <typename T>
struct HasVirtualDestructor : BoolConstant<HasVirtualDestructor_V<T>> {};

