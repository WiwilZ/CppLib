//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "TypeModification/Reference/AddRValueReference.h"


namespace traits {
    template <typename T>
    AddRValueReference_T<T> DeclVal() noexcept {
        static_assert(false, "DeclVal not allowed in an evaluated context");
    }
}
