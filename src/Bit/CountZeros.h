//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountOnes.h"
#include "../Concept/Integral.h"



namespace Bit {
    template <Concept::Integral T>
    [[nodiscard]] constexpr int CountZeros(T x) noexcept {
        return CountOnes(~x);
    }
}
