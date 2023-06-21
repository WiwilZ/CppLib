//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_fundamental)
namespace Trait {
    template <typename T>
    constexpr bool IsFundamental_V = __is_fundamental(T);
}
#else // !HAS_BUILTIN(__is_fundamental)
#include "Fundamental/IsArithmetic.h"
#include "Fundamental/IsVoid.h"
#include "Fundamental/IsNullPointer.h"


namespace Trait {
    template <typename T>
    constexpr bool IsFundamental_V = IsArithmetic_V<T> || IsVoid_V<T> || IsNullPointer_V<T>;
}
#endif


namespace Trait {
    template <typename T>
    struct IsFundamental : BoolConstant<IsFundamental_V<T>> {};
}
