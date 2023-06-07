//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "MakeLValueReference.h"
#include "MakeRValueReference.h"
#include "RemoveReference.h"
#include "../Void_T.h"


namespace Trait {

    namespace Detail {

        template <typename T>
        struct ApplyReference {
            template <typename U>
            using Apply = RemoveReference_T<U>;
        };

        template <typename T>
        struct ApplyReference<T&> {
            template <typename U>
            using Apply = MakeLValueReference_T<U>;
        };

        template <typename T>
        struct ApplyReference<T&&> {
            template <typename U>
            using Apply = MakeRValueReference_T<U>;
        };

    } // namespace Detail


    template <typename From, typename To>
    using ApplyReference_T = typename Detail::ApplyReference<From>::template Apply<To>;


    template <typename From, typename To>
    struct ApplyReference {
        using Type = ApplyReference_T<From, To>;
    };

} // namespace Trait



