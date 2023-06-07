//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if __has_builtin(__is_function)

namespace Trait {

    template <typename T>
    constexpr bool IsFunction_V = __is_function(T);

} // namespace Trait

#else // __has_builtin(__is_function)

#include "../../Property/IsConst.h"
#include "IsReference.h"


namespace Trait {

    template <typename T>
    constexpr bool IsFunction_V = !IsConst_V<const T> && !IsReference_V<T>; // Only function types and reference types can't be const qualified

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsFunction : BoolConstant<IsFunction_V<T>> {};

} // namespace Trait
