//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if HAS_BUILTIN(__is_member_function_pointer)
namespace traits {
    template <typename T>
    constexpr bool IsMemberFunctionPointer_V = __is_member_function_pointer(T);
}
#else // !HAS_BUILTIN(__is_member_function_pointer)
#include "../IsFunction.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace traits {
    namespace Detail {
        template <typename T>
        constexpr bool IsMemberFunctionPointer_V = false;

        template <typename T, typename U>
        constexpr bool IsMemberFunctionPointer_V<T U::*> = IsFunction_V<T>;
    }

    template <typename T>
    constexpr bool IsMemberFunctionPointer_V = Detail::IsMemberFunctionPointer_V<RemoveCV_T<T>>;
}
#endif


namespace traits {
    template <typename T>
    struct IsMemberFunctionPointer : BoolConstant<IsMemberFunctionPointer_V<T>> {};
}

