//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if HAS_BUILTIN(__is_compound)

namespace Trait {

    template <typename T>
    constexpr bool IsCompound_V = __is_compound(T);

} // namespace Trait

#else // !HAS_BUILTIN(__is_compound)

#include "IsFundamental.h"


namespace Trait {

    template <typename T>
    constexpr bool IsCompound_V = !IsFundamental_V<T>;

} // namespace Trait

#endif


namespace Trait {
    template <typename T>
    struct IsCompound : BoolConstant<IsCompound_V<T>> {};
}
