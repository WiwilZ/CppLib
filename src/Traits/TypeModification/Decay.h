//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "Conditional.h"
#include "../TypeProperty/Category/Compound/IsArray.h"
#include "../TypeProperty/Category/Compound/IsFunction.h"
#include "CVSpecifier/RemoveCV.h"
#include "Array/RemoveExtent.h"
#include "Pointer/AddPointer.h"


namespace traits {

    template <typename T>
    struct Decay : Conditional<IsArray_V<T>,
            AddPointer_T<RemoveExtent_T<T>>,
            Conditional_T<IsFunction_V<T>, AddPointer_T<T>, RemoveCV_T<T>>> {};


    template <typename T>
    using Decay_T = typename Decay<T>::Type;

} // namespace traits

