//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_const)

namespace Trait {

    template <typename T>
    constexpr bool IsConst_V = __is_const(T);

} // namespace Trait

#else // !__has_builtin(__is_const)

namespace Trait {

    template <typename T>
    constexpr bool IsConst_V = false;

    template <typename T>
    constexpr bool IsConst_V<const T> = true;

} // namespace Trait

#endif // __has_builtin(__is_const)


namespace Trait {

    template <typename T>
    struct IsConst : BoolConstant<IsConst_V<T>> {};

} // namespace Trait

