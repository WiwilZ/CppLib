//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../IsFunction.h"
#include "../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../../Constant.h"


namespace Trait {

    namespace Detail {

        template <typename T>
        constexpr bool IsFunctionPointer_V = false;

        template <typename T>
        constexpr bool IsFunctionPointer_V<T*> = IsFunction_V<T>;

    } // namespace Detail


    template <typename T>
    constexpr bool IsFunctionPointer_V = Detail::IsFunctionPointer_V<RemoveCV_T<T>>;


    template <typename T>
    struct IsFunctionPointer : BoolConstant<IsFunctionPointer_V<T>> {};

} // namespace Trait

