//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if HAS_BUILTIN(__is_lvalue_reference)

namespace Trait {

    template <typename T>
    constexpr bool IsLValueReference_V = __is_lvalue_reference(T);

} // namespace Trait

#else // HAS_BUILTIN(__is_lvalue_reference)

namespace Trait {

    template <typename T>
    constexpr bool IsLValueReference_V = false;

    template <typename T>
    constexpr bool IsLValueReference_V<T&> = true;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsLValueReference : BoolConstant<IsLValueReference_V<T>> {};

} // namespace Trait

