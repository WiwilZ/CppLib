//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


#if HAS_BUILTIN(__is_pointer_interconvertible_base_of) || defined(_MSC_VER) && !defined(__clang__)
namespace Trait {
    template <typename Base, typename Derived>
    constexpr bool IsPointerInterconvertibleBaseOf_V = __is_pointer_interconvertible_base_of(Base, Derived);


    template <typename Base, typename Derived>
    struct IsPointerInterconvertibleBaseOf : BoolConstant<IsPointerInterconvertibleBaseOf_V<Base, Derived>> {};
}
#endif
