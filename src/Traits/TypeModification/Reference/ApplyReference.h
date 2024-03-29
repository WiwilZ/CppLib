//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "MakeLValueReference.h"
#include "MakeRValueReference.h"
#include "RemoveReference.h"
#include "../Void_T.h"


namespace traits {
    namespace detail {
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
    }


    template <typename From, typename To>
    using ApplyReference_T = typename detail::ApplyReference<From>::template Apply<To>;


    template <typename From, typename To>
    struct ApplyReference {
        using Type = ApplyReference_T<From, To>;
    };
}



