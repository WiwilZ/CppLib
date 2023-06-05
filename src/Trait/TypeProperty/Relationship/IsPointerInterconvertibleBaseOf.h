//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__is_pointer_interconvertible_base_of) || defined(_MSC_VER) && !defined(__clang__)

template <typename Base, typename Derived>
constexpr bool IsPointerInterconvertibleBaseOf_V = __is_pointer_interconvertible_base_of(Base, Derived);


template <typename Base, typename Derived>
struct IsPointerInterconvertibleBaseOf : BoolConstant<IsPointerInterconvertibleBaseOf_V<Base, Derived>> {};

#endif // __has_builtin(__is_pointer_interconvertible_base_of) || defined(_MSC_VER) && !defined(__clang__)
