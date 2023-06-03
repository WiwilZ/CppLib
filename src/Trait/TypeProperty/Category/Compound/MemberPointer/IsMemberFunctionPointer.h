//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../../Macro.h"
#include "../../../../Constant.h"


#if __has_builtin(__is_member_function_pointer)

template <typename T>
constexpr bool IsMemberFunctionPointer_V = __is_member_function_pointer(T);

#else

#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../IsFunction.h"


namespace Detail {
    template <typename T>
    constexpr bool IsMemberFunctionPointer_V = false;

    template <typename T, typename U>
    constexpr bool IsMemberFunctionPointer_V<T U::*> = IsFunction_V<T>;
}

template <typename T>
constexpr bool IsMemberFunctionPointer_V = Detail::IsMemberFunctionPointer_V<RemoveCV_T<T>>;

#endif // __has_builtin(__is_member_function_pointer)


template <typename T>
struct IsMemberFunctionPointer : BoolConstant<IsMemberFunctionPointer_V<T>> {};
