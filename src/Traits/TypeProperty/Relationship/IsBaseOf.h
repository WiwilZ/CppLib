//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../Macro.h"
#include "../../Constant.h"


#if HAS_BUILTIN(__is_base_of) || defined(_MSC_VER)
namespace traits {
    template <typename Base, typename Derived>
    constexpr bool IsBaseOf_V = __is_base_of(Base, Derived);
}
#else // !(HAS_BUILTIN(__is_base_of) || defined(_MSC_VER))
#include "../../TypeModification/Void_T.h"
#include "../Category/Compound/IsClass.h"


namespace traits {
    namespace detail {
        template <typename T>
        traits::TrueType TestIsBaseOf(const volatile T*);

        template <typename T>
        traits::FalseType TestIsBaseOf(...);


        template <typename Base, typename Derived>
        using IsBaseOf = decltype(TestIsBaseOf<Base>(static_cast<Derived*>(nullptr)));


        template <typename Base, typename Derived, typename = void>
        constexpr bool IsBaseOf_V = true;

        template <typename Base, typename Derived>
        constexpr bool IsBaseOf_V<Base, Derived, Void_T<IsBaseOf<Base, Derived>>> = IsBaseOf<Base, Derived>::Value;
    }

    template <typename Base, typename Derived>
    constexpr bool IsBaseOf_V = IsClass_V<Base> && IsClass_V<Derived> && detail::IsBaseOf_V<Base, Derived>;
}
#endif


namespace traits {
    template <typename Base, typename Derived>
    struct IsBaseOf : BoolConstant<IsBaseOf_V<Base, Derived>> {};
}

