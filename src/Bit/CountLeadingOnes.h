//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountLeadingZeros.h"
#include "../Concepts/Integral.h"



template <concepts::Integral T>
[[nodiscard]] constexpr int CountLeadingOnes(T x) noexcept {
    return ::CountLeadingZeros(~x);
}
