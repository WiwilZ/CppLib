//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../../Constant.h"
#include "../../../../Macro.h"


#if HAS_BUILTIN(__is_enum) || defined(_MSC_VER)
namespace traits {
    template <typename T>
    constexpr bool IsEnum_V = __is_enum(T);
}
#else // !HAS_BUILTIN(__is_enum) && !defined(_MSC_VER)
#include "../IsFundamental.h"
#include "IsArray.h"
#include "IsFunction.h"
#include "IsPointer.h"
#include "IsReference.h"
#include "IsMemberPointer.h"
#include "../../../TypeModification/CVSpecifier/RemoveCV.h"


namespace traits {
    namespace Detail {
        template <typename T>
        constexpr bool IsClassOrUnion_V = false;

        template <typename T>
        constexpr bool IsClassOrUnion_V<int T::*> = true;
    }

    template <typename T>
    constexpr bool IsEnum_V = !(IsFundamental_V<T> || IsArray_V<T> || IsFunction_V<T> || IsPointer_V<T> || IsReference_V<T> || IsMemberPointer_V<T> || Detail::IsClassOrUnion_V<RemoveCV_T<T>>);
}
#endif


namespace traits {
    template <typename T>
    struct IsEnum : BoolConstant<IsEnum_V<T>> {};
}
