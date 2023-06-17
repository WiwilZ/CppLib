//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "BitLength.h"
#include "../Concept/Integral.h"
#include "../Trait/IntegralTrait.h"



namespace Bit {
    template <Concept::Integral T>
    [[nodiscard]] constexpr T BitCeil(T x) noexcept {
        if (x <= 1) {
            return 1;
        }
        const int shift = BitLength(x - 1);
        if (shift >= Trait::IntegralTrait<T>::NumDigits) {
            return 0;
        }
        return static_cast<T>(1) << shift;
    }
}

