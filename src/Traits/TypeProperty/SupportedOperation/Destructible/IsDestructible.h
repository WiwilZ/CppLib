//
// Created by WiwilZ on 2023/5/31.
//

#pragma once

#include "../../../Constant.h"


#if HAS_BUILTIN(__is_destructible) || defined(_MSC_VER)
namespace traits {
    template <typename T>
    constexpr bool IsDestructible_V = __is_destructible(T);
}
#else // !( HAS_BUILTIN(__is_destructible) || defined(_MSC_VER))
#include "../../../TypeModification/Array/RemoveAllExtents.h"
#include "../../../TypeProperty/Category/IsObject.h"
#include "../../../TypeProperty/Category/Compound/IsReference.h"
#include "../../../TypeProperty/Category/Fundamental/IsVoid.h"
#include "../../../TypeProperty/Category/Compound/IsFunction.h"
#include "../../../TypeProperty/Category/Compound/Array/IsUnboundedArray.h"
#include "../../../DeclVal.h"


namespace traits {
    namespace detail {
        template <typename T>
        constexpr bool IsDestructible_V = requires{ traits::DeclVal<T&>().~T(); };
    }

    template <typename T>
    constexpr bool IsDestructible_V = IsReference_V<T> || !(IsVoid_V<T> || IsFunction_V<T> || IsUnboundedArray_V<T>) || detail::IsDestructible_V<RemoveAllExtents_T<T>>;
}
#endif


namespace traits {
    template <typename T>
    struct IsDestructible : BoolConstant<IsDestructible_V<T>> {};
}

