//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountLeadingZeros_BitLength.h"
#include "../Concept/Integer.h"


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountLeadingOnes(T x) noexcept {
        return CountLeadingZeros(~x);
    }

} // namespace Bit
