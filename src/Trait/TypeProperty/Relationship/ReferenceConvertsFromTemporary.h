//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__reference_converts_from_temporary)

template <typename T1, typename T2>
constexpr bool ReferenceConvertsFromTemporary_V = __reference_converts_from_temporary(T1, T2);


template <typename T1, typename T2>
struct ReferenceConvertsFromTemporary : BoolConstant<ReferenceConvertsFromTemporary_V<T1, T2>> {};

#endif // __has_builtin(__reference_converts_from_temporary)
