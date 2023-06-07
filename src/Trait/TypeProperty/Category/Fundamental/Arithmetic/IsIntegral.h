//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if __has_builtin(__is_integral)

namespace Trait {

    template <typename T>
    constexpr bool IsIntegral_V = __is_integral(T);

} // namespace Trait

#elif defined(_MSC_VER)

#include "Integral/IsInteger.h"
#include "Integral/IsCharacter.h"


namespace Trait {

    template <typename T>
    constexpr bool IsIntegral_V = IsInteger_V<T> || IsCharacter_V<T>;

} // namespace Trait

#else // !__has_builtin(__is_integral) && !_MSC_VER

namespace Trait {

    template <typename T>
    constexpr bool IsIntegral_V = requires(T t, T* p, void f(T)) {
        reinterpret_cast<T>(t); // 排除类类型
        f(0); // 排除枚举类型
        p + t; // 排除所有尚未排除的类型
    };

}  // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsIntegral : BoolConstant<IsIntegral_V<T>> {};

} // namespace Trait
