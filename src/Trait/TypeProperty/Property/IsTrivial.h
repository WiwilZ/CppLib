//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_trivial)

namespace Trait {

    template <typename T>
    constexpr bool IsTrivial_V = __is_trivial(T);

} // namespace Trait

#else // !__has_builtin(__is_trivial)

namespace Trait {

    template <typename T>
    constexpr bool IsTrivial_V = __is_trivially_constructible(T) && __is_trivially_copyable(T);

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsTrivial : BoolConstant<IsTrivial_V<T>> {};

} // namespace Trait
