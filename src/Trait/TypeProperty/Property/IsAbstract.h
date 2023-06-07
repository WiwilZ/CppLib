//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../Constant.h"
#include "../../../Macro.h"


#if __has_builtin(__is_abstract) || defined(_MSC_VER)

namespace Trait {

    template <typename T>
    constexpr bool IsAbstract_V = __is_abstract(T);

} // namespace Trait

#else // !(__has_builtin(__is_abstract) || defined(_MSC_VER))

#include "../Category/Compound/IsClass.h"


namespace Trait {

    template <typename T>
    constexpr bool IsAbstract_V = IsClass_V<T> && !requires{ static_cast<T(*)[1]>(nullptr); };

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsAbstract : BoolConstant<IsAbstract_V<T>> {};

} // namespace Trait

