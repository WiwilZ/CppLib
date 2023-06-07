//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../Concept/Enum.h"


namespace Trait {

    template <Concept::Enum T>
    struct UnderlyingType {
        using Type = __underlying_type(T);
    };


    template <Concept::Enum T>
    using UnderlyingType_T = typename UnderlyingType<T>::Type;

} // namespace Trait

