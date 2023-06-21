//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_nothrow_assignable) || defined(_MSC_VER)
namespace Trait {
    template <typename T, typename U>
    constexpr bool IsNothrowAssignable_V = __is_nothrow_assignable(T, U);
}
#else // !(HAS_BUILTIN(__is_nothrow_assignable) || defined(_MSC_VER))
#include "../../../DeclVal.h"


namespace Trait {
    template <typename T, typename U>
    constexpr bool IsNothrowAssignable_V = requires{
        requires noexcept(Trait::DeclVal<T>() = Trait::DeclVal<U>());
    };
}
#endif


namespace Trait {
    template <typename T, typename U>
    struct IsNothrowAssignable : BoolConstant<IsNothrowAssignable_V<T, U>> {};
}