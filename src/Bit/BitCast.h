//
// Created by WiwilZ on 2023/6/1.
//

#pragma once

#include "../Concept/TriviallyCopyable.h"



namespace Bit {
    template <Concept::TriviallyCopyable To, Concept::TriviallyCopyable From>
    requires (sizeof(To) == sizeof(From))
    [[nodiscard]] constexpr To BitCast(const From& v) noexcept {
        return __builtin_bit_cast(To, v);
    }
}

