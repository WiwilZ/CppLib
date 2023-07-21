//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../Void_T.h"


namespace traits {
    namespace detail {
        template <typename T, typename = void>
        struct AddRValueReference {
            using Type = T;
        };

        template <typename T>
        struct AddRValueReference<T, Void_T<T&&>> {
            using Type = T&&;
        };
    }


    template<typename T>
    struct AddRValueReference : detail::AddRValueReference<T> {};


    template<typename T>
    using AddRValueReference_T = typename AddRValueReference<T>::Type;
}
