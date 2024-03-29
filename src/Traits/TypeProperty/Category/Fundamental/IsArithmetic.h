//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if HAS_BUILTIN(__is_arithmetic)
namespace traits {
    template <typename T>
    constexpr bool IsArithmetic_V = __is_arithmetic(T);
}
#else // !HAS_BUILTIN(__is_arithmetic)
#include "Arithmetic/IsIntegral.h"
#include "Arithmetic/IsFloatingPoint.h"


namespace traits {
    template <typename T>
    constexpr bool IsArithmetic_V = IsIntegral_V<T> || IsFloatingPoint_V<T>;
}
#endif


namespace traits {
    template <typename T>
    struct IsArithmetic : BoolConstant<IsArithmetic_V<T>> {};
}
