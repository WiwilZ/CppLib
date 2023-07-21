//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if HAS_BUILTIN(__is_pointer)
namespace traits {
    template <typename T>
    constexpr bool IsPointer_V = __is_pointer(T);
}
#else // HAS_BUILTIN(__is_pointer)
#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace traits {
    namespace Detail {
        template <typename T>
        constexpr bool IsPointer_V = false;

        template <typename T>
        constexpr bool IsPointer_V<T*> = true;
    }

    template <typename T>
    constexpr bool IsPointer_V = Detail::IsPointer_V<RemoveCV_T<T>>;
}
#endif


namespace traits {
    template <typename T>
    struct IsPointer : BoolConstant<IsPointer_V<T>> {};
}

