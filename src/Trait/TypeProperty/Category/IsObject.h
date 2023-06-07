//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_object)

namespace Trait {

    template <typename T>
    constexpr bool IsObject_V = __is_object(T);

}

#else // !__has_builtin(__is_object)

#include "../Property/IsConst.h"
#include "Fundamental/IsVoid.h"


namespace Trait {

    template <typename T>
    constexpr bool IsObject_V = IsConst_V<const T> && !IsVoid_V<T>; // `IsConst_V<const T>` excludes function types and reference types

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsObject : BoolConstant<IsObject_V<T>> {};

} // namespace Trait

