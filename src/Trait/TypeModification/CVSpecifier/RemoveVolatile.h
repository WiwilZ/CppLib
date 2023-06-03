//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


template <typename T>
struct RemoveVolatile {
    using Type = T;
};

template <typename T>
struct RemoveVolatile<volatile T> {
    using Type = T;
};


template <typename T>
using RemoveVolatile_T = typename RemoveVolatile<T>::Type;
