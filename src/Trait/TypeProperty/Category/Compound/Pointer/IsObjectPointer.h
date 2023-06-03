//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../IsFunction.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../../Constant.h"


namespace Detail {
template <typename T>
    constexpr bool IsObjectPointer_V = false;

    template <typename T>
    constexpr bool IsObjectPointer_V<T*> = !IsFunction_V<T>;
}

template <typename T>
constexpr bool IsObjectPointer_V = Detail::IsObjectPointer_V<RemoveCV_T<T>>;


template <typename T>
struct IsObjectPointer : BoolConstant<IsObjectPointer_V<T>> {};
