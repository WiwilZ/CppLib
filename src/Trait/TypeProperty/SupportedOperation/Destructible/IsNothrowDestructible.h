//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Macro.h"
#include "../../../Constant.h"


#if __has_builtin(__is_nothrow_destructible) || defined(_MSC_VER)

template <typename T>
constexpr bool IsNothrowDestructible_V = __is_nothrow_destructible(T);

#else

#include "IsDestructible.h"
#include "../../../DeclVal.h"
#include "../../../TypeModification/Array/RemoveAllExtents.h"


namespace Detail {
    template <typename T>
    constexpr bool IsNothrowDestructible_V = noexcept(::DeclVal<T&>().~T());
}

template <typename T>
constexpr bool IsNothrowDestructible_V = IsDestructible_V<T> && Detail::IsNothrowDestructible_V<RemoveAllExtents_T<T>>;


#endif // __has_builtin(__is_nothrow_destructible) || defined(_MSC_VER)


template <typename T>
struct IsNothrowDestructible : BoolConstant<IsNothrowDestructible_V<T>> {};

