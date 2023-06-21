//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "TypeModification/Reference/AddRValueReference.h"
#include "../Trait/AlwaysFalse.h"


namespace Trait {
    template <typename T>
    AddRValueReference_T<T> DeclVal() noexcept {
        static_assert(AlwaysFalse<T>, "DeclVal not allowed in an evaluated context");
    }
}
