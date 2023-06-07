//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../Void_T.h"


namespace Trait {

    namespace Detail {

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

    } // namespace Detail


    template <typename T>
    struct MakeRValueReference : Detail::MakeRValueReference<T> {};


    template <typename T>
    using MakeRValueReference_T = typename MakeRValueReference<T>::Type;

} // namespace Trait
