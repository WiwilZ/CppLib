//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountTrailingZeros.h"
#include "../Concept/IntegerType.h"

#include <cstdint>


template <IntegerType T>
[[nodiscard]] constexpr int CountTrailingOnes(T x) noexcept {
    return CountTrailingZeros(~x);
}
