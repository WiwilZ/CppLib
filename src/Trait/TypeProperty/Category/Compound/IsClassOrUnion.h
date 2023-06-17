//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if HAS_BUILTIN(__is_class) && HAS_BUILTIN(__is_union) || defined(_MSC_VER)

namespace Trait {

    template <typename T>
    constexpr bool IsClassOrUnion_V = __is_class(T) || __is_union(T);

} // namespace Trait

#else // !(HAS_BUILTIN(__is_class) && HAS_BUILTIN(__is_union) || defined(_MSC_VER))

namespace Trait {

    template <typename T>
    constexpr bool IsClassOrUnion_V = false;

    template <typename T>
    constexpr bool IsClassOrUnion_V<int T::*> = true;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsClassOrUnion : BoolConstant<IsClassOrUnion_V<T>> {};

} // namespace Trait

