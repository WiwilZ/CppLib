//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if HAS_BUILTIN(__is_void)
namespace Trait {
    template <typename T>
    constexpr bool IsVoid_V = __is_void(T);
}
#else // !HAS_BUILTIN(__is_void)
#include "../../Relationship/IsSame.h"
#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Trait {
    template <typename T>
    constexpr bool IsVoid_V = IsSame_V<RemoveCV_T<T>, void>;
}
#endif


namespace Trait {
    template <typename T>
    struct IsVoid : BoolConstant<IsVoid_V<T>> {};
}
