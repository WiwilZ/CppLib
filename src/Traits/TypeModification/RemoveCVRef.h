//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "Reference/RemoveReference.h"
#include "CVSpecifier/RemoveCV.h"


namespace traits {
    template <typename T>
    struct RemoveCVRef {
        using Type = RemoveCV_T<RemoveReference_T<T>>;
    };


    template <typename T>
    using RemoveCVRef_T = typename RemoveCVRef<T>::Type;
}

