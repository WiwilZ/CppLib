//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_referenceable)

namespace Trait {

    template <typename T>
    constexpr bool IsReferencable_V = __is_referenceable(T);

} // namespace Trait

#else // !__has_builtin(__is_referenceable)

#include "../../TypeModification/Void_T.h"


namespace Trait {

    namespace Detail {

        template <typename T, typename = void>
        constexpr bool IsReferencable_V = false;

        template <typename T>
        constexpr bool IsReferencable_V<T, Void_T<T&>> = true;

    } // namespace Detail


    template <typename T>
    constexpr bool IsReferencable_V = Detail::IsReferencable_V<T>;

} // namespace Trait

#endif // __has_builtin(__is_referenceable)


namespace Trait {

    template <typename T>
    struct IsReferencable : BoolConstant<IsReferencable_V<T>> {};

} // namespace Trait
