//
// Created by WiwilZ on 2023/6/17.
//

#pragma once

#include "BitLength.h"
#include "../Concept/Integral.h"
#include "../Trait/IntegralTrait.h"



namespace Bit {
    template <Concept::Integral T>
    [[nodiscard]] constexpr int CountLeadingZeros(T x) noexcept {
        return Trait::IntegralTrait<T>::NumBits - BitLength(x);
    }
}

