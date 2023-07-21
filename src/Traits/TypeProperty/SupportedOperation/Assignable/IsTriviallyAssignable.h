//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


namespace traits {
    template <typename T, typename U>
    constexpr bool IsTriviallyAssignable_V = __is_trivially_assignable(T, U);


    template <typename T, typename U>
    struct IsTriviallyAssignable : BoolConstant<IsTriviallyAssignable_V<T, U>> {};
}

