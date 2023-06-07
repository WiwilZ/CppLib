//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"
#include "../../.../../../../Macro.h"


#if __has_builtin(__is_member_pointer)

namespace Trait {

    template <typename T>
    constexpr bool IsMemberPointer_V = __is_member_pointer(T);

} // namespace Trait

#else // __has_builtin(__is_member_pointer)

#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Trait {

    namespace Detail {

        template <typename T>
        constexpr bool IsMemberPointer_V = false;

        template <typename T, typename U>
        constexpr bool IsMemberPointer_V<T U::*> = true;

    } // namespace Detail


    template <typename T>
    constexpr bool IsMemberPointer_V = Detail::IsMemberPointer_V<RemoveCV_T<T>>;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsMemberPointer : BoolConstant<IsMemberPointer_V<T>> {};

} // namespace Trait

