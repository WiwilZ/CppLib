//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountTrailingZeros.h"
#include "../Concept/Integer.h"


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountTrailingOnes(T x) noexcept {
        return CountTrailingZeros(~x);
    }

} // namespace Bit

