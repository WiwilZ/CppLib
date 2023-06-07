//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if __has_builtin(__is_member_object_pointer)

namespace Trait {

    template <typename T>
    constexpr bool IsMemberObjectPointer_V = __is_member_object_pointer(T);

} // namespace Trait

#else // !__has_builtin(__is_member_object_pointer)

#include "../IsFunction.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace Trait {

    namespace Detail {

        template <typename T>
        constexpr bool IsMemberObjectPointer_V = false;

        template <typename T, typename U>
        constexpr bool IsMemberObjectPointer_V<T U::*> = !IsFunction_V<T>;

    } // namespace Detail


    template <typename T>
    constexpr bool IsMemberObjectPointer_V = Detail::IsMemberObjectPointer_V<RemoveCV_T<T>>;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsMemberObjectPointer : BoolConstant<IsMemberObjectPointer_V<T>> {};

} // namespace Trait

