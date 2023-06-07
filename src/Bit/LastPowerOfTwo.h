//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "BitLength.h"
#include "../Concept/Integer.h"


namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr T LastPowerOf2(T x) noexcept {
        if (x <= 1) {
            return 0;
        }
        return static_cast<T>(1) << (BitLength(x) - 2);
    }

} // namespace Bit

