//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../Concepts/Enum.h"


namespace traits {
    template <concepts::Enum T>
    struct UnderlyingType {
        using Type = __underlying_type(T);
    };


    template <concepts::Enum T>
    using UnderlyingType_T = typename UnderlyingType<T>::Type;
}

