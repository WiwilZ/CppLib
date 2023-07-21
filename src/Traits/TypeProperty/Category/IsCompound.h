//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_compound)
namespace traits {
    template <typename T>
    constexpr bool IsCompound_V = __is_compound(T);
}
#else // !HAS_BUILTIN(__is_compound)
#include "IsFundamental.h"


namespace traits {
    template <typename T>
    constexpr bool IsCompound_V = !IsFundamental_V<T>;
}
#endif


namespace traits {
    template <typename T>
    struct IsCompound : BoolConstant<IsCompound_V<T>> {};
}
