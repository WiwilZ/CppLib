//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../RemoveCVRef.h"
#include "../Reference/RemoveReference.h"
#include "../Reference/ApplyReference.h"


namespace traits {
    namespace detail {
        template <typename T>
        struct ApplyCV {
            template <typename U>
            using Apply = ApplyReference_T<U, RemoveCVRef_T<U>>;
        };

        template <typename T>
        struct ApplyCV<const T> {
            template <typename U>
            using Apply = ApplyReference_T<U, const RemoveCVRef_T<U>>;
        };

        template <typename T>
        struct ApplyCV<volatile T> {
            template <typename U>
            using Apply = ApplyReference_T<U, volatile RemoveCVRef_T<U>>;
        };

        template <typename T>
        struct ApplyCV<const volatile T> {
            template <typename U>
            using Apply = ApplyReference_T<U, const volatile RemoveCVRef_T<U>>;
        };
    }


    template <typename From, typename To>
    using ApplyCV_T = typename detail::ApplyCV<RemoveReference_T<From>>::template Apply<To>;


    template <typename From, typename To>
    struct ApplyCV {
        using Type = ApplyCV_T<From, To>;
    };
}

