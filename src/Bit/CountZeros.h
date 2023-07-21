//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountOnes.h"
#include "../Concepts/Integral.h"
#include "../ArithmeticType.h"


template <concepts::Integral T>
[[nodiscard]] constexpr usize CountZeros(T x) noexcept {
    return ::CountOnes(~x);
}
