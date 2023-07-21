//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include <cstddef>
#include <cstdint>


using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;


#ifdef __SIZEOF_INT128__
#define HAS_INT128 1
using i128 = __int128_t;
using u128 = __uint128_t;
#else
#define HAS_INT128 0
#endif



using isize = ptrdiff_t;
using usize = size_t;



using f32 = float;
using f64 = double;
