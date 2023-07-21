//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../../../ArithmeticType.h"
#include "../../../../../Relationship/IsAnyOf.h"
#include "../../../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsUnsignedInteger_V = IsAnyOf_V<RemoveCV_T<T>, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long
#if HAS_INT128
            , u128
#endif
    >;


    template <typename T>
    struct IsUnsignedInteger : BoolConstant<IsUnsignedInteger_V<T>> {};
}

