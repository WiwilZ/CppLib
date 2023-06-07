//
// Created by WiwilZ on 2023/6/1.
//

#pragma once

#include "../Trait/TypeProperty/Property/IsTriviallyCopyable.h"


namespace Bit {

    template <typename To, typename From>
    requires (sizeof(To) == sizeof(From) && Trait::IsTriviallyCopyable_V<To> && Trait::IsTriviallyCopyable_V<From>)
    [[nodiscard]] constexpr To BitCast(const From& v) noexcept {
        return __builtin_bit_cast(To, v);
    }

} // namespace Bit

