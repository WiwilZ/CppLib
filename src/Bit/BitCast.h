//
// Created by WiwilZ on 2023/6/1.
//

#pragma once

#include "../Trait/TypeProperty/Property/IsTriviallyCopyable.h"


template <typename To, typename From>
requires (sizeof(To) == sizeof(From) && IsTriviallyCopyable_V<To> && IsTriviallyCopyable_V<From>)
[[nodiscard]] constexpr To BitCast(const From& v) noexcept {
    return __builtin_bit_cast(To, v);
}
