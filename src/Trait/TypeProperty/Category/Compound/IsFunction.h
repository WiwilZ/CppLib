//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if HAS_BUILTIN(__is_function)
namespace Trait {
    template <typename T>
    constexpr bool IsFunction_V = __is_function(T);
}
#else // HAS_BUILTIN(__is_function)
#include "../../Property/IsConst.h"
#include "IsReference.h"


namespace Trait {
    template <typename T>
    constexpr bool IsFunction_V = !IsConst_V<const T> && !IsReference_V<T>; // Only function types and reference types can't be const qualified
}
#endif


namespace Trait {
    template <typename T>
    struct IsFunction : BoolConstant<IsFunction_V<T>> {};
}
