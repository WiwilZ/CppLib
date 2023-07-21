//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_referenceable)
namespace traits {
    template <typename T>
    constexpr bool IsReferencable_V = __is_referenceable(T);
}
#else // !HAS_BUILTIN(__is_referenceable)
#include "../../TypeModification/Void_T.h"


namespace traits {
    namespace Detail {
        template <typename T, typename = void>
        constexpr bool IsReferencable_V = false;

        template <typename T>
        constexpr bool IsReferencable_V<T, Void_T<T&>> = true;
    }


    template <typename T>
    constexpr bool IsReferencable_V = Detail::IsReferencable_V<T>;
}
#endif


namespace traits {
    template <typename T>
    struct IsReferencable : BoolConstant<IsReferencable_V<T>> {};
}
