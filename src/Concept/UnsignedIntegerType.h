//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../Trait/TypeModification/CVSpecifier/RemoveCV.h"
#include "../Trait/TypeProperty/Relationship/IsAnyOf.h"


template <typename T>
concept UnsignedIntegerType = IsAnyOf_V<RemoveCV_T<T>, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long
#ifdef __SIZEOF_INT128__
        , __uint128_t
#endif // __SIZEOF_INT128__
>;
