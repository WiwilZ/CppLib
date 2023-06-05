//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "BitLength.h"
#include "../Trait/IntegralTrait.h"
#include "../Concept/UnsignedIntegerType.h"

#include <cstdint>


template <UnsignedIntegerType T>
[[nodiscard]] constexpr T BitCeil(T x) noexcept {
    if (x <= 1) {
        return 1;
    }
    const int shift = BitLength(x - 1);
    if (shift >= IntegralTrait<T>::NumBits) {
        return 0;
    }
    return static_cast<T>(1) << shift;
}
