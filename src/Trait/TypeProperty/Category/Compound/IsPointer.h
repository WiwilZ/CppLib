//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Macro.h"
#include "../../../Constant.h"


#if __has_builtin(__is_pointer)

template <typename T>
constexpr bool IsPointer_V = __is_pointer(T);

#else

#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Detail {
    template <typename T>
    constexpr bool IsPointer_V = false;

    template <typename T>
    constexpr bool IsPointer_V<T*> = true;
}

template <typename T>
constexpr bool IsPointer_V = Detail::IsPointer_V<RemoveCV_T<T>>;

#endif // __has_builtin(__is_pointer)


template <typename T>
struct IsPointer : BoolConstant<IsPointer_V<T>> {};
