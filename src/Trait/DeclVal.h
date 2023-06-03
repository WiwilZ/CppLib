//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "TypeModification/Reference/AddRValueReference.h"


namespace Detail::DeclVal {
    template <typename>
    constexpr bool AlwaysFalse = false;
}

template <typename T>
AddRValueReference_T<T> DeclVal() noexcept {
    static_assert(Detail::DeclVal::AlwaysFalse<T>, "DeclVal not allowed in an evaluated context");
}
