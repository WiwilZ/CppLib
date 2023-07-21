//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_nothrow_destructible) || defined(_MSC_VER)
namespace traits {
    template <typename T>
    constexpr bool IsNothrowDestructible_V = __is_nothrow_destructible(T);
}
#else // !(HAS_BUILTIN(__is_nothrow_destructible) || defined(_MSC_VER))
#include "IsDestructible.h"
#include "../../../TypeModification/Array/RemoveAllExtents.h"
#include "../../../DeclVal.h"


namespace traits {
    namespace Detail {
        template <typename T>
        constexpr bool IsNothrowDestructible_V = noexcept(traits::DeclVal<T&>().~T());
    }

    template <typename T>
    constexpr bool IsNothrowDestructible_V = IsDestructible_V<T> && Detail::IsNothrowDestructible_V<RemoveAllExtents_T<T>>;
}
#endif


namespace traits {
    template <typename T>
    struct IsNothrowDestructible : BoolConstant<IsNothrowDestructible_V<T>> {};
}

