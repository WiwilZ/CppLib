//
// Created by WiwilZ on 2023/6/1.
//

#pragma once


template <typename To, typename From>
requires (sizeof(To) == sizeof(From) && __is_trivially_copyable(To) && __is_trivially_copyable(From))
[[nodiscard]] constexpr To BitCast(const From& v) noexcept {
    return __builtin_bit_cast(To, v);
}
