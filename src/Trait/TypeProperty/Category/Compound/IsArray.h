//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include <cstddef>
#include "../../../Constant.h"


template <typename T>
constexpr bool IsArray_V = false;

template <typename T>
constexpr bool IsArray_V<T[]> = true;

template <typename T, std::size_t N>
constexpr bool IsArray_V<T[N]> = true;


template <typename T>
struct IsArray : BoolConstant<IsArray_V<T>> {};
