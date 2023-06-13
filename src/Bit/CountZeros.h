//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountOnes.h"
#include "../Concept/Integer.h"


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountZeros(T x) noexcept {
        return CountOnes(~x);
    }

} // namespace Bit
