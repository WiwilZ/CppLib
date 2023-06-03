//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include <cstdint>
#include "../BitCast.h"
#include "../../Concept.h"
#include "../../Trait.h"


namespace Detail::Common {

    constexpr uint8_t BitLengthTable[256]{
            0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
    };


    constexpr int BitLengthImpl(float x) noexcept {
        return (BitCast<uint32_t>(x) >> 23) - 0x7f + 1;
    }

    constexpr int BitLengthImpl(double x) noexcept {
        return (BitCast<uint64_t>(x) >> 52) - 0x3ff + 1;
    }


    template <UnsignedIntegral T>
    constexpr int BitLength(T x) noexcept {
        if constexpr (sizeof(T) == 1) {
            return BitLengthTable[x];
        } else if constexpr (sizeof(T) == 2) {
            return BitLengthImpl(static_cast<float>(x));
        } else if constexpr (sizeof(T) == 4) {
            return BitLengthImpl(static_cast<double>(x));
        } else if constexpr (sizeof(T) == 8) {
#ifdef __AVX512F__
            if (!__builtin_is_constant_evaluated()) {
                __m128 tmp;
                return BitLengthImpl(_mm_cvtss_f32(_mm_cvt_roundu64_ss(tmp, x, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC)));
            }
#endif
            uint32_t high = x >> 32;
            if (high != 0) {
                return BitLengthImpl(static_cast<double>(high));
            }
            uint32_t low = x;
            return 32 + BitLengthImpl(static_cast<double>(low));
        } else {
            int n = 0;
            if (x >= T{1} << 64) {
                x >>= 64;
                n = 64;
            }
            if (x >= T{1} << 32) {
                x >>= 32;
                n += 32;
            }
            if (x >= T{1} << 16) {
                x >>= 16;
                n += 16;
            }
            if (x >= T{1} << 8) {
                x >>= 8;
                n += 8;
            }
            return n + BitLengthTable[x];
        }
    }

} // namespace Detail::Common
