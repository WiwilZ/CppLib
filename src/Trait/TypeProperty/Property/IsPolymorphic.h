//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_polymorphic) || defined(_MSC_VER)

template <typename T>
constexpr bool IsPolymorphic_V = __is_polymorphic(T);

#else

template <typename T>
constexpr bool IsPolymorphic_V = requires{ dynamic_cast<const volatile void*>(static_cast<T*>(nullptr)); };

#endif // __has_builtin(__is_polymorphic) || defined(_MSC_VER)


template <typename T>
struct IsPolymorphic : BoolConstant<IsPolymorphic_V<T>> {};

