//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountTrailingZeros.h"
#include "../Concepts/Integral.h"



template <concepts::Integral T>
[[nodiscard]] constexpr int CountTrailingOnes(T x) noexcept {
    return ::CountTrailingZeros(~x);
}
