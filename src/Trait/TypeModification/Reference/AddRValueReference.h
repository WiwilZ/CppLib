//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../Void_T.h"


namespace Trait {

    namespace Detail {

        template <typename T, typename = void>
        struct AddRValueReference {
            using Type = T;
        };

        template <typename T>
        struct AddRValueReference<T, Void_T<T&&>> {
            using Type = T&&;
        };

    } // namespace Detail


    template<typename T>
    struct AddRValueReference : Detail::AddRValueReference<T> {};


    template<typename T>
    using AddRValueReference_T = typename AddRValueReference<T>::Type;

} // namespace Trait
