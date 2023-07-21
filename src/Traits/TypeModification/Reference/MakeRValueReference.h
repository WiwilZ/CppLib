//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../Void_T.h"


namespace traits {
    namespace detail {
        template <typename T>
        struct MakeRValueReferenceImpl {
            using Type = T&&;
        };

        template <typename T>
        struct MakeRValueReferenceImpl<T&> {
            using Type = T&&;
        };

        template <typename T, typename = void>
        struct MakeRValueReference {
            using Type = T;
        };

        template <typename T>
        struct MakeRValueReference<T, Void_T<T&&>> : MakeRValueReferenceImpl<T> {};
    }


    template <typename T>
    struct MakeRValueReference : detail::MakeRValueReference<T> {};


    template <typename T>
    using MakeRValueReference_T = typename MakeRValueReference<T>::Type;
}
