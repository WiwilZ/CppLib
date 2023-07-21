//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if HAS_BUILTIN(__is_floating_point)
namespace traits {
    template <typename T>
    constexpr bool IsFloatingPoint_V = __is_floating_point(T);
}
#else // !HAS_BUILTIN(__is_floating_point)
#include "../../../Relationship/IsAnyOf.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace traits {
    template <typename T>
    constexpr bool IsFloatingPoint_V = IsAnyOf_V<RemoveCV_T<T>, float, double, long double>;
}
#endif


namespace traits {
    template <typename T>
    struct IsFloatingPoint : BoolConstant<IsFloatingPoint_V<T>> {};
}

