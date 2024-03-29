//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_scalar)
namespace traits {
    template <typename T>
    constexpr bool IsScalar_V = __is_scalar(T);
}
#else // !HAS_BUILTIN(__is_scalar)
#include "Fundamental/IsArithmetic.h"
#include "Compound/IsPointer.h"
#include "Compound/IsMemberPointer.h"
#include "Compound/IsEnum.h"
#include "Fundamental/IsNullPointer.h"


namespace traits {
    template <typename T>
    constexpr bool IsScalar_V = IsArithmetic_V<T> || IsPointer_V<T> || IsMemberPointer_V<T> || IsEnum_V<T> || IsNullPointer_V<T>;
}
#endif


namespace traits {
    template <typename T>
    struct IsScalar : BoolConstant<IsScalar_V<T>> {};
}