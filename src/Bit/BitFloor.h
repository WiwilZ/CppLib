//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "BitLength.h"
#include "../Concepts/Integral.h"



template <concepts::Integral T>
[[nodiscard]] constexpr T BitFloor(T x) noexcept {
    if (x <= 0) {
        return 0;
    }
    return static_cast<T>(1) << (BitLength(x) - 1);
}
