//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include <cstdint>
#include "../Concept.h"
#include "../Trait.h"

#if !(defined(__GNUC__) || defined(__clang__))
#include "Common/BitLength.h"
#endif



template <UnsignedIntegral T>
[[nodiscard]] constexpr int BitLength(T x) noexcept {
#if defined(__GNUC__) || defined(__clang__)
    return IntegralTrait<T>::NumBits - CountLeadingZeros(x);
#else
    return Detail::Common::BitLength(x);
#endif
}

