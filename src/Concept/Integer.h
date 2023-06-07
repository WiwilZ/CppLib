//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "SignedInteger.h"
#include "UnsignedInteger.h"


namespace Concept {

    template <typename T>
    concept Integer = SignedInteger<T> || UnsignedInteger<T>;

} // namespace Concept
