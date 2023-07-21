//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if HAS_BUILTIN(__is_member_object_pointer)
namespace traits {
    template <typename T>
    constexpr bool IsMemberObjectPointer_V = __is_member_object_pointer(T);
}
#else // !HAS_BUILTIN(__is_member_object_pointer)
#include "../IsFunction.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace traits {
    namespace detail {
        template <typename T>
        constexpr bool IsMemberObjectPointer_V = false;

        template <typename T, typename U>
        constexpr bool IsMemberObjectPointer_V<T U::*> = !IsFunction_V<T>;
    }

    template <typename T>
    constexpr bool IsMemberObjectPointer_V = detail::IsMemberObjectPointer_V<RemoveCV_T<T>>;
}
#endif


namespace traits {
    template <typename T>
    struct IsMemberObjectPointer : BoolConstant<IsMemberObjectPointer_V<T>> {};
}

