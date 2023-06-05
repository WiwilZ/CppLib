//
// Created by WiwilZ on 2023/5/29.
//

#pragma once


#include <cstdint>
#include <cstddef>


using int8 = int8_t;
using uint8 = uint8_t;
using int16 = int16_t;
using uint16 = uint16_t;
using int32 = int32_t;
using uint32 = uint32_t;
using int64 = int64_t;
using uint64 = uint64_t;


#ifdef __SIZEOF_INT128__
    using int128 = __int128_t;
    using uint128 = __uint128_t;
#endif

