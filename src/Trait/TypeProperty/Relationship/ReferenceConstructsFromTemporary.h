//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__reference_constructs_from_temporary)

template <typename T1, typename T2>
constexpr bool ReferenceConstructsFromTemporary_V = __reference_constructs_from_temporary(T1, T2);


template <typename T1, typename T2>
struct ReferenceConstructsFromTemporary : BoolConstant<ReferenceConstructsFromTemporary_V<T1, T2>> {};

#endif // __has_builtin(__reference_constructs_from_temporary)