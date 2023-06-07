//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool HasUniqueObjectRepresentations_V = __has_unique_object_representations(T);


    template <typename T>
    struct HasUniqueObjectRepresentations : BoolConstant<HasUniqueObjectRepresentations_V<T>> {};

} // namespace Trait
