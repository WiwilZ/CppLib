//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if __has_builtin(__is_member_object_pointer)

template <typename T>
constexpr bool IsMemberObjectPointer_V = __is_member_object_pointer(T);

#else

#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../IsFunction.h"


namespace Detail {
    template <typename T>
    constexpr bool IsMemberObjectPointer_V = false;

    template <typename T, typename U>
    constexpr bool IsMemberObjectPointer_V<T U::*> = !IsFunction_V<T>;
}

template <typename T>
constexpr bool IsMemberObjectPointer_V = Detail::IsMemberObjectPointer_V<RemoveCV_T<T>>;

#endif // __has_builtin(__is_member_object_pointer)


template <typename T>
struct IsMemberObjectPointer : BoolConstant<IsMemberObjectPointer_V<T>> {};
