//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include <cstddef>
#include <cstdint>

#include "Traits/TypeModification/SignModifier/MakeSigned.h"



using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;


#ifdef __SIZEOF_INT128__
using i128 = __int128_t;
using u128 = __uint128_t;
#endif



using isize = traits::MakeSigned_T<size_t>;
using usize = size_t;



using f32 = float;
using f64 = double;
