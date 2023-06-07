//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "CountTrailingZeros.h"
#include "../Concept/Integer.h"


#if defined(_MSC_VER) && !defined(__clang__)
#   pragma warning(push)
#   pragma warning(disable : 4146)
#endif



namespace Bit {

    template <Concept::Integer T>
    [[nodiscard]] constexpr int CountTrailingOnes(T x) noexcept {
        return CountTrailingZeros(~x);
    }

} // namespace Bit



#if defined(_MSC_VER) && !defined(__clang__)
#   pragma warning(push)
#   pragma warning(disable : 4146)
#endif

