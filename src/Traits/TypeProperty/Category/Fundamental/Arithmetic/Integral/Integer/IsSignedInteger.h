//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../Relationship/IsAnyOf.h"
#include "../../../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsSignedInteger_V = IsAnyOf_V<RemoveCV_T<T>, signed char, signed short, signed int, signed long, signed long long
#ifdef __SIZEOF_INT128__
            , __int128_t
#endif // __SIZEOF_INT128__
    >;


    template <typename T>
    struct IsSignedInteger : BoolConstant<IsSignedInteger_V<T>> {};
}

