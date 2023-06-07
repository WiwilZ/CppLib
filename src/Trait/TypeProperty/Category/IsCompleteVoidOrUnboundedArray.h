//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "Fundamental/IsVoid.h"
#include "Compound/IsReference.h"
#include "Compound/IsFunction.h"
#include "Compound/Array/IsUnboundedArray.h"
#include "../../Constant.h"


namespace Trait {

    template <typename T>
    constexpr bool IsCompleteVoidOrUnboundedArray_V = requires { sizeof(T); } || IsVoid_V<T> || IsReference_V<T> || IsFunction_V<T> || IsUnboundedArray_V<T>;


    template <typename T>
    struct IsCompleteVoidOrUnboundedArray : BoolConstant<IsCompleteVoidOrUnboundedArray_V<T>> {};

} // namespace Trait

