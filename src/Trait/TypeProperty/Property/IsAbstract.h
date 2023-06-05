//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_abstract) || defined(_MSC_VER)

template <typename T>
constexpr bool IsAbstract_V = __is_abstract(T);

#else

#include "../Category/Compound/IsClass.h"


template <typename T>
constexpr bool IsAbstract_V = IsClass_V<T> && !requires{ static_cast<T(*)[1]>(nullptr); };

#endif // __has_builtin(__is_abstract) || defined(_MSC_VER)


template <typename T>
struct IsAbstract : BoolConstant<IsAbstract_V<T>> {};
