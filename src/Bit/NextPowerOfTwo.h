//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "BitLength.h"
#include "../Concepts/Integral.h"
#include "../Traits/IntegralTrait.h"



template <concepts::Integral T>
[[nodiscard]] constexpr T NextPowerOf2(T x) noexcept {
    if (x == 0) {
        return 1;
    }
    const int shift = BitLength(x);
    if (shift >= traits::IntegralTrait<T>::NumDigits) {
        return 0;
    }
    return static_cast<T>(1) << shift;
}
