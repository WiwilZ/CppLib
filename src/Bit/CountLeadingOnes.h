//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountLeadingZeros.h"
#include "../Concept/IntegerType.h"

#include <cstdint>


template <IntegerType T>
[[nodiscard]] constexpr int CountLeadingOnes(T x) noexcept {
    return CountLeadingZeros(~x);
}
