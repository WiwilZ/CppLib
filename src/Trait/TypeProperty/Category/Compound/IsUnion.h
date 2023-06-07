//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool IsUnion_V = __is_union(T);


    template <typename T>
    struct IsUnion : BoolConstant<IsUnion_V<T>> {};

} // namespace Trait

