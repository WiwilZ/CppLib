//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include <cstddef>
#include "../../Constant.h"


template <typename T>
constexpr std::size_t AlignmentOf_V = alignof(T);


template <typename T>
struct AlignmentOf : SizeConstant<AlignmentOf_V<T>> {};
