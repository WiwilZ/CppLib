//
// Created by WiwilZ on 2023/6/8.
//

#pragma once

#include "../Category/Compound/IsClass.h"
#include "../../Constant.h"


namespace traits {
    template <typename Derived, typename Base>
    constexpr bool IsPublicDerivedFrom_V = IsClass_V<Derived> && IsClass_V<Base> && requires(void f(const volatile Base*)) {
        f(static_cast<const volatile Derived*>(nullptr));
    };


    template <typename Derived, typename Base>
    struct IsPublicDerivedFrom : BoolConstant<IsPublicDerivedFrom_V<Derived, Base>> {};
}

