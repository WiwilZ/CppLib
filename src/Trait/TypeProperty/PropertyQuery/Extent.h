//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include <cstddef>
#include "../../Constant.h"


template <typename T, unsigned I = 0>
constexpr std::size_t Extent_V = 0;

template <typename T>
constexpr std::size_t Extent_V<T[], 0> = 0;

template <typename T, std::size_t N>
constexpr std::size_t Extent_V<T[N], 0> = 0;

template <typename T, unsigned I>
constexpr std::size_t Extent_V<T[], I> = Extent_V<T, I - 1>;


template <typename T>
struct Extent : SizeConstant<Extent_V<T>> {};
