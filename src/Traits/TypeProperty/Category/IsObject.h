//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_object)
namespace traits {
    template <typename T>
    constexpr bool IsObject_V = __is_object(T);
}
#else // !HAS_BUILTIN(__is_object)
#include "../Property/IsConst.h"
#include "Fundamental/IsVoid.h"


namespace traits {
    template <typename T>
    constexpr bool IsObject_V = IsConst_V<const T> && !IsVoid_V<T>; // `IsConst_V<const T>` excludes function types and reference types
}
#endif


namespace traits {
    template <typename T>
    struct IsObject : BoolConstant<IsObject_V<T>> {};
}

