//
// Created by WiwilZ on 2023/6/17.
//

#pragma once

#include "BitLength.h"
#include "../Concepts/Integral.h"
#include "../Traits/IntegralTrait.h"



template <concepts::Integral T>
[[nodiscard]] constexpr int CountLeadingZeros(T x) noexcept {
    return traits::IntegralTrait<T>::NumBits - ::BitLength(x);
}

