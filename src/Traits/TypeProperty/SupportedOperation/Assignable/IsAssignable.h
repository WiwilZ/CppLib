//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_assignable) || defined(_MSC_VER)
namespace traits {
    template <typename T, typename U>
    constexpr bool IsAssignable_V = __is_assignable(T, U);
}
#else // !(HAS_BUILTIN(__is_assignable) || defined(_MSC_VER))
#include "../../../DeclVal.h"


namespace traits {
    template <typename T, typename U>
    constexpr bool IsAssignable_V = requires { traits::DeclVal<T>() = traits::DeclVal<U>(); };
}
#endif


namespace traits {
    template <typename T, typename U>
    struct IsAssignable : BoolConstant<IsAssignable_V<T, U>> {};
}