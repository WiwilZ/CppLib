//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "../Concept/IntegerType.h"

#include <cstdint>


template <IntegerType T>
[[nodiscard]] constexpr bool IsPowerOfTwo(T x) noexcept {
    return x > 0 && (x & (x - 1)) == 0;
}
