//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Macro.h"
#include "../../../Constant.h"


#if __has_builtin(__is_member_pointer)

template <typename T>
constexpr bool IsMemberPointer_V = __is_member_pointer(T);

#else

#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Detail {
    template <typename T>
    constexpr bool IsMemberPointer_V = false;

    template <typename T, typename U>
    constexpr bool IsMemberPointer_V<T U::*> = true;
}

template <typename T>
constexpr bool IsMemberPointer_V = Detail::IsMemberPointer_V<RemoveCV_T<T>>;

#endif // __has_builtin(__is_member_pointer)


template <typename T>
struct IsMemberPointer : BoolConstant<IsMemberPointer_V<T>> {};
