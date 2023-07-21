//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "../ArithmeticType.h"
#include <climits>
#include <cfloat>


namespace traits {
    template <typename T>
    struct FloatingPointTrait;

    template <>
    struct FloatingPointTrait<float> {
        static constexpr usize NumBytes = sizeof(float);
        static constexpr usize NumBits = NumBytes * CHAR_BIT;
        static constexpr usize NumDigits = FLT_MANT_DIG;
        static constexpr usize NumDigits10 = FLT_DIG;
        static constexpr usize NumMaxDigits10 = 2 + NumDigits * 30103L / 100000L;
        static constexpr int MinExponent = FLT_MIN_EXP;
        static constexpr int MaxExponent = FLT_MAX_EXP;
        static constexpr int MinExponent10 = FLT_MIN_10_EXP;
        static constexpr int MaxExponent10 = FLT_MAX_10_EXP;

        static constexpr float Min = FLT_MIN;
        static constexpr float Max = FLT_MAX;
        static constexpr float AbsMin = -Max;
        static constexpr float Epsilon = FLT_EPSILON;
        static constexpr float RoundError = 0.5f;
        static constexpr float Infinity = __builtin_huge_valf();
        static constexpr float QuietNaN = __builtin_nanf("");
        static constexpr float SignalingNaN = __builtin_nansf("");
        static constexpr float DenormMin =
#if defined(_MSC_VER) && !defined(__clang__)
                FLT_TRUE_MIN;
#else
                __FLT_DENORM_MIN__;
#endif
    };

    template <>
    struct FloatingPointTrait<double> {
        static constexpr usize NumBytes = sizeof(double);
        static constexpr usize NumBits = NumBytes * CHAR_BIT;
        static constexpr usize NumDigits = DBL_MANT_DIG;
        static constexpr usize NumDigits10 = DBL_DIG;
        static constexpr usize NumMaxDigits10 = 2 + NumDigits * 30103L / 100000L;
        static constexpr int MinExponent = DBL_MIN_EXP;
        static constexpr int MaxExponent = DBL_MAX_EXP;
        static constexpr int MinExponent10 = DBL_MIN_10_EXP;
        static constexpr int MaxExponent10 = DBL_MAX_10_EXP;

        static constexpr double Min = DBL_MIN;
        static constexpr double Max = DBL_MAX;
        static constexpr double AbsMin = -Max;
        static constexpr double Epsilon = DBL_EPSILON;
        static constexpr double RoundError = 0.5;
        static constexpr double Infinity = __builtin_huge_val();
        static constexpr double QuietNaN = __builtin_nan("");
        static constexpr double SignalingNaN = __builtin_nans("");
        static constexpr double DenormMin =
#if defined(_MSC_VER) && !defined(__clang__)
                DBL_TRUE_MIN;
#else
                __DBL_DENORM_MIN__;
#endif
    };


#if defined(_WIN32) || defined(__arm__) || defined(__NVPTX__) || defined(__AMDGPU__) || defined(__APPLE__) && defined(__aarch64__)
    template <>
    struct FloatingPointTrait<long double> : FloatingPointTrait<double> {};
#else
    template <>
    struct FloatingPointTrait<long double> {
        static constexpr usize NumBytes = sizeof(long double);
        static constexpr usize NumBits = NumBytes * CHAR_BIT;
        static constexpr usize NumDigits = LDBL_MANT_DIG;
        static constexpr usize NumDigits10 = LDBL_DIG;
        static constexpr usize NumMaxDigits10 = 2 + NumDigits * 30103L / 100000L;
        static constexpr int MinExponent = LDBL_MIN_EXP;
        static constexpr int MaxExponent = LDBL_MAX_EXP;
        static constexpr int MinExponent10 = LDBL_MIN_10_EXP;
        static constexpr int MaxExponent10 = LDBL_MAX_10_EXP;

        static constexpr long double Min = LDBL_MIN;
        static constexpr long double Max = LDBL_MAX;
        static constexpr long double AbsMin = -Max;
        static constexpr long double Epsilon = LDBL_EPSILON;
        static constexpr long double RoundError = 0.5L;
        static constexpr long double Infinity = __builtin_huge_vall();
        static constexpr long double QuietNaN = __builtin_nanl("");
        static constexpr long double SignalingNaN = __builtin_nansl("");
        static constexpr long double DenormMin = __LDBL_DENORM_MIN__;
    };
#endif
}