//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"


namespace Trait {
    template <typename T>
    constexpr bool IsTriviallyCopyable_V = __is_trivially_copyable(T);


    template <typename T>
    struct IsTriviallyCopyable : BoolConstant<IsTriviallyCopyable_V<T>> {};
}
