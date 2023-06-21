//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"
#include "../../.../../../../Macro.h"


#if HAS_BUILTIN(__is_member_pointer)
namespace Trait {
    template <typename T>
    constexpr bool IsMemberPointer_V = __is_member_pointer(T);
}
#else // HAS_BUILTIN(__is_member_pointer)
#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Trait {
    namespace Detail {
        template <typename T>
        constexpr bool IsMemberPointer_V = false;

        template <typename T, typename U>
        constexpr bool IsMemberPointer_V<T U::*> = true;
    }

    template <typename T>
    constexpr bool IsMemberPointer_V = Detail::IsMemberPointer_V<RemoveCV_T<T>>;
}
#endif


namespace Trait {
    template <typename T>
    struct IsMemberPointer : BoolConstant<IsMemberPointer_V<T>> {};
}
