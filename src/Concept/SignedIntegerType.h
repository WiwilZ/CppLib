//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeModification/CVSpecifier/RemoveCV.h"
#include "../Trait/TypeProperty/Relationship/IsAnyOf.h"


template <typename T>
concept SignedIntegerType = IsAnyOf_V<RemoveCV_T<T>, signed char, signed short, signed int, signed long, signed long long
#ifdef __SIZEOF_INT128__
        , __int128_t
#endif // __SIZEOF_INT128__
>;

