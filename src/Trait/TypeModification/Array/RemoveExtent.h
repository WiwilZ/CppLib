//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include <cstddef>


namespace Trait {

    template <typename T>
    struct RemoveExtent {
        using Type = T;
    };

    template <typename T, std::size_t N>
    struct RemoveExtent<T[N]> {
        using Type = T;
    };

    template <typename T>
    struct RemoveExtent<T[]> {
        using Type = T;
    };


    template <typename T>
    using RemoveExtent_T = typename RemoveExtent<T>::Type;

} // namespace Trait

