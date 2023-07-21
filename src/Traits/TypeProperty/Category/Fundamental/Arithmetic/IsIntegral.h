//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if HAS_BUILTIN(__is_integral)
namespace traits {
    template <typename T>
    constexpr bool IsIntegral_V = __is_integral(T);
}
#elif defined(_MSC_VER)
#include "Integral/IsInteger.h"
#include "Integral/IsCharacter.h"


namespace traits {
    template <typename T>
    constexpr bool IsIntegral_V = IsInteger_V<T> || IsCharacter_V<T>;
}
#else // !HAS_BUILTIN(__is_integral) && !defined(_MSC_VER)
namespace traits {
    template <typename T>
    constexpr bool IsIntegral_V = requires(T t, T* p, void f(T)) {
        reinterpret_cast<T>(t); // exclude class-like types
        f(0); // exclude enum types
        p + t; // exclude other types
    };
}
#endif


namespace traits {
    template <typename T>
    struct IsIntegral : BoolConstant<IsIntegral_V<T>> {};
}
