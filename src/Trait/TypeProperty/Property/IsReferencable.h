//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if __has_builtin(__is_referenceable)

template <typename T>
constexpr bool IsReferencable_V = __is_referenceable(T);

#else

#include "../../TypeModification/Void_T.h"


namespace Detail {
    template <typename T, typename = void>
    constexpr bool IsReferencable_V = false;

    template <typename T>
    constexpr bool IsReferencable_V<T, Void_T<T&>> = true;
}

template <typename T>
constexpr bool IsReferencable_V = Detail::IsReferencable_V<T>;

#endif // __has_builtin(__is_referenceable)


template <typename T>
struct IsReferencable : BoolConstant<IsReferencable_V<T>> {};

