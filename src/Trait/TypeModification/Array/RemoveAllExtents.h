//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include <cstddef>


template <typename T>
struct RemoveAllExtents {
    using Type = T;
};


template <typename T>
using RemoveAllExtents_T = typename RemoveAllExtents<T>::Type;


template <typename T, std::size_t N>
struct RemoveAllExtents<T[N]> {
    using Type = RemoveAllExtents_T<T>;
};

template <typename T>
struct RemoveAllExtents<T[]> {
    using Type = RemoveAllExtents_T<T>;
};


