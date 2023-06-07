//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if __has_builtin(__is_floating_point)

namespace Trait {

    template <typename T>
    constexpr bool IsFloatingPoint_V = __is_floating_point(T);

} // namespace Trait

#else // !__has_builtin(__is_floating_point)

#include "../../../Relationship/IsAnyOf.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Trait {

    template <typename T>
    constexpr bool IsFloatingPoint_V = IsAnyOf_V<RemoveCV_T<T>, float, double, long double>;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsFloatingPoint : BoolConstant<IsFloatingPoint_V<T>> {};

} // namespace Trait

