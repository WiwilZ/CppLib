//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../../../../Constant.h"

#include <cstddef>


namespace traits {
    template <typename T>
    constexpr bool IsBoundedArray_V = false;

    template <typename T, std::size_t N>
    constexpr bool IsBoundedArray_V<T[N]> = true;


    template <typename T>
    struct IsBoundedArray : BoolConstant<IsBoundedArray_V<T>> {};
}

