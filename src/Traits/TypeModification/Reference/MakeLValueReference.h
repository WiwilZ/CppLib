//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "AddLValueReference.h"


namespace traits {
    template <typename T>
    struct MakeLValueReference : AddLValueReference<T> {};


    template <typename T>
    using MakeLValueReference_T = typename MakeLValueReference<T>::Type;
}

