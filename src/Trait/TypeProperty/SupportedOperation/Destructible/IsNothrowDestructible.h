//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if __has_builtin(__is_nothrow_destructible) || defined(_MSC_VER)

namespace Trait {

    template <typename T>
    constexpr bool IsNothrowDestructible_V = __is_nothrow_destructible(T);

} // namespace Trait

#else // !(__has_builtin(__is_nothrow_destructible) || defined(_MSC_VER))

#include "IsDestructible.h"
#include "../../../TypeModification/Array/RemoveAllExtents.h"
#include "../../../DeclVal.h"


namespace Trait {

    namespace Detail {

        template <typename T>
        constexpr bool IsNothrowDestructible_V = noexcept(Trait::DeclVal<T&>().~T());

    } // namespace Detail


    template <typename T>
    constexpr bool IsNothrowDestructible_V = IsDestructible_V<T> && Detail::IsNothrowDestructible_V<RemoveAllExtents_T<T>>;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsNothrowDestructible : BoolConstant<IsNothrowDestructible_V<T>> {};

} // namespace Trait
