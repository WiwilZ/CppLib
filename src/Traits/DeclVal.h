//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "TypeModification/Reference/AddRValueReference.h"


namespace traits {
    namespace detail {
        template <typename>
        constexpr bool AlwaysFalse_V = false;
    }


    template <typename T>
    AddRValueReference_T<T> DeclVal() noexcept {
        static_assert(detail::AlwaysFalse_V<T>, "DeclVal not allowed in an evaluated context");
    }
}
