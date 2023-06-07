//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include <climits>
#include <cfloat>


namespace Trait {

    template <typename T>
    struct FloatingPointTrait;

    template <>
    struct FloatingPointTrait<float> {
        static constexpr int NumBytes = sizeof(float);
        static constexpr int NumBits = NumBytes * CHAR_BIT;
        static constexpr int NumDigits = FLT_MANT_DIG;
        static constexpr int NumDigits10 = FLT_DIG;
        static constexpr int NumMaxDigits10 = 2 + NumDigits * 30103L / 100000L;
        static constexpr int MaxExponent = FLT_MIN_EXP;
        static constexpr int MaxExponent10 = FLT_MIN_10_EXP;
        static constexpr int MinExponent = FLT_MAX_EXP;
        static constexpr int MinExponent10 = FLT_MAX_10_EXP;

        static constexpr float Min = FLT_MIN;
        static constexpr float Max = FLT_MAX;
        static constexpr float AbsMin = -Max;
        static constexpr float Epsilon = FLT_EPSILON;
        static constexpr float RoundError = 0.5f;
        static constexpr float Infinity = __builtin_huge_valf();
        static constexpr float QuietNaN = __builtin_nanf("");
        static constexpr float SignalingNaN = __builtin_nansf("");
        static constexpr float DenormMin =
#ifdef _MSC_VER
                FLT_TRUE_MIN;
#else // !defined(_MSC_VER)
                __FLT_DENORM_MIN__;
#endif
    };

    template <>
    struct FloatingPointTrait<double> {
        static constexpr int NumBytes = sizeof(double);
        static constexpr int NumBits = NumBytes * CHAR_BIT;
        static constexpr int NumDigits = DBL_MANT_DIG;
        static constexpr int NumDigits10 = DBL_DIG;
        static constexpr int NumMaxDigits10 = 2 + NumDigits * 30103L / 100000L;
        static constexpr int MaxExponent = DBL_MIN_EXP;
        static constexpr int MaxExponent10 = DBL_MIN_10_EXP;
        static constexpr int MinExponent = DBL_MAX_EXP;
        static constexpr int MinExponent10 = DBL_MAX_10_EXP;

        static constexpr double Min = DBL_MIN;
        static constexpr double Max = DBL_MAX;
        static constexpr double AbsMin = -Max;
        static constexpr double Epsilon = DBL_EPSILON;
        static constexpr double RoundError = 0.5;
        static constexpr double Infinity = __builtin_huge_val();
        static constexpr double QuietNaN = __builtin_nan("");
        static constexpr double SignalingNaN = __builtin_nans("");
        static constexpr double DenormMin =
#ifdef _MSC_VER
                DBL_TRUE_MIN;
#else // !defined(_MSC_VER)
                __DBL_DENORM_MIN__;
#endif // _MSC_VER
    };


#ifdef _MSC_VER

    template <>
    struct FloatingPointTrait<long double> : FloatingPointTrait<double> {};

#else // !defined(_MSC_VER)

    template <>
    struct FloatingPointTrait<long double> {
        static constexpr int NumBytes = sizeof(long double);
        static constexpr int NumBits = NumBytes * CHAR_BIT;
        static constexpr int NumDigits = LDBL_MANT_DIG;
        static constexpr int NumDigits10 = LDBL_DIG;
        static constexpr int NumMaxDigits10 = 2 + NumDigits * 30103L / 100000L;
        static constexpr int MaxExponent = LDBL_MIN_EXP;
        static constexpr int MaxExponent10 = LDBL_MIN_10_EXP;
        static constexpr int MinExponent = LDBL_MAX_EXP;
        static constexpr int MinExponent10 = LDBL_MAX_10_EXP;

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

} // namespace Trait