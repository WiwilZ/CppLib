//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Macro.h"
#include "../../../Constant.h"


#if __has_builtin(__is_void)

template <typename T>
constexpr bool IsVoid_V = __is_void(T);

#else

#include "../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../Relationship/IsSame.h"


template <typename T>
constexpr bool IsVoid_V = IsSame_V<RemoveCV_T<T>, void>;

#endif // __has_builtin(__is_void)


template <typename T>
struct IsVoid : BoolConstant<IsVoid_V<T>> {};

