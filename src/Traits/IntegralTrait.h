//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../ArithmeticType.h"
#include <climits>
#include "../Concepts/Integral.h"


namespace traits {
    template <typename T>
    struct IntegralTrait;


    template <concepts::Integral T>
    struct IntegralTrait<T> {
        static constexpr bool IsSigned = static_cast<T>(-1) < static_cast<T>(0);
        static constexpr bool IsModulo = !IsSigned;
        static constexpr usize NumBytes = sizeof(T);
        static constexpr usize NumBits = NumBytes * CHAR_BIT;
        static constexpr usize NumDigits = NumBits - IsSigned;
        static constexpr usize NumDigits10 = NumDigits * 3 / 10;
        static constexpr T Min = IsSigned ? static_cast<T>(1) << NumDigits : static_cast<T>(0);
        static constexpr T Max = IsSigned ? ~(static_cast<T>(1) << NumDigits) : ~static_cast<T>(0);
    };


    template <>
    struct IntegralTrait<bool> {
        static constexpr bool IsSigned = false;
        static constexpr bool IsModulo = false;
        static constexpr usize NumBytes = sizeof(bool);
        static constexpr usize NumBits = NumBytes * CHAR_BIT;
        static constexpr usize NumDigits = 1;
        static constexpr usize NumDigits10 = 0;
        static constexpr bool Min = false;
        static constexpr bool Max = true;
    };
}
