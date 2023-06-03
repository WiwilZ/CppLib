//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include <cstddef>
#include "../../Constant.h"


template <typename T>
constexpr std::size_t Rank_V = 0;

template <typename T>
constexpr std::size_t Rank_V<T[]> = Rank_V<T> + 1;

template <typename T, std::size_t N>
constexpr std::size_t Rank_V<T[N]> = Rank_V<T> + 1;


template <typename T>
struct Rank : SizeConstant<Rank_V<T>> {};
