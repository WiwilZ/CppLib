//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if __has_builtin(__is_destructible) || defined(_MSC_VER)

namespace Trait {

    template <typename T>
    constexpr bool IsDestructible_V = __is_destructible(T);

} // namespace Trait

#else // !( __has_builtin(__is_destructible) || defined(_MSC_VER))

#include "../../../TypeModification/Array/RemoveAllExtents.h"
#include "../../../TypeProperty/Category/IsObject.h"
#include "../../../TypeProperty/Category/Compound/IsReference.h"
#include "../../../TypeProperty/Category/Fundamental/IsVoid.h"
#include "../../../TypeProperty/Category/Compound/IsFunction.h"
#include "../../../TypeProperty/Category/Compound/Array/IsUnboundedArray.h"
#include "../../../DeclVal.h"


namespace Trait {

    namespace Detail {

        template <typename T>
        constexpr bool IsDestructible_V = requires{ Trait::DeclVal<T&>().~T(); };

    } // namespace Detail


    template <typename T>
    constexpr bool IsDestructible_V = IsReference_V<T> || !(IsVoid_V<T> || IsFunction_V<T> || IsUnboundedArray_V<T>) || Detail::IsDestructible_V<RemoveAllExtents_T<T>>;

} // namespace Trait

#endif


namespace Trait {

    template <typename T>
    struct IsDestructible : BoolConstant<IsDestructible_V<T>> {};

} // namespace Trait

