//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_compound)

template <typename T>
constexpr bool IsCompound_V = __is_compound(T);

#else

#include "IsFundamental.h"


template <typename T>
constexpr bool IsCompound_V = !IsFundamental_V<T>;

#endif // __has_builtin(__is_compound)


template <typename T>
struct IsCompound : BoolConstant<IsCompound_V<T>> {};
