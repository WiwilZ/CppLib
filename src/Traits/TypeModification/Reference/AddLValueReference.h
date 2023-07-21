//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../Void_T.h"


namespace traits {
    namespace detail {
        template <typename T, typename = void>
        struct AddLValueReference {
            using Type = T;
        };

        template <typename T>
        struct AddLValueReference<T, Void_T<T&>> {
            using Type = T&;
        };
    }


    template <typename T>
    struct AddLValueReference : detail::AddLValueReference<T> {};


    template <typename T>
    using AddLValueReference_T = typename AddLValueReference<T>::Type;
}

