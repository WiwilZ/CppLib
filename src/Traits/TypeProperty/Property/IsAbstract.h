//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_abstract) || defined(_MSC_VER)
namespace traits {
    template <typename T>
    constexpr bool IsAbstract_V = __is_abstract(T);
}
#else // !(HAS_BUILTIN(__is_abstract) || defined(_MSC_VER))
#include "../Category/Compound/IsClass.h"


namespace traits {
    template <typename T>
    constexpr bool IsAbstract_V = IsClass_V<T> && !requires{ static_cast<T(*)[1]>(nullptr); };
}
#endif


namespace traits {
    template <typename T>
    struct IsAbstract : BoolConstant<IsAbstract_V<T>> {};
}

