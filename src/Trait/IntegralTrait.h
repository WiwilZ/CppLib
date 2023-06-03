//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include <climits>
#include "../Concept/Arithmetic.h"


template <typename T>
struct IntegralTrait;


template <Integral T>
struct IntegralTrait<T> {
    static constexpr bool IsSigned = static_cast<T>(-1) < static_cast<T>(0);
    static constexpr bool IsModulo = !IsSigned;
    static constexpr int NumBytes = sizeof(T);
    static constexpr int NumBits = NumBytes * CHAR_BIT;
    static constexpr int NumDigits = NumBits - IsSigned;
    static constexpr int NumDigits10 = NumDigits * 3 / 10;
    static constexpr T Min = IsSigned ? static_cast<T>(1) << NumDigits : static_cast<T>(0);
    static constexpr T Max = IsSigned ? ~(static_cast<T>(1) << NumDigits): ~static_cast<T>(0);
};


template <>
struct IntegralTrait<bool> {
    static constexpr bool IsSigned = false;
    static constexpr bool IsModulo = false;
    static constexpr int NumBytes = sizeof(bool);
    static constexpr int NumBits = NumBytes * CHAR_BIT;
    static constexpr int NumDigits = 1;
    static constexpr int NumDigits10 = 0;
    static constexpr bool Min = false;
    static constexpr bool Max = true;
};
