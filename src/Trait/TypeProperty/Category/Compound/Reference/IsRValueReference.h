//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if HAS_BUILTIN(__is_rvalue_reference)

namespace Trait {

    template <typename T>
    constexpr bool IsRValueReference_V = __is_rvalue_reference(T);

} // namespace Trait

#else // HAS_BUILTIN(__is_rvalue_reference)

namespace Trait {

    template <typename T>
    constexpr bool IsRValueReference_V = false;

    template <typename T>
    constexpr bool IsRValueReference_V<T&&> = true;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsRValueReference : BoolConstant<IsRValueReference_V<T>> {};

} // namespace Trait

