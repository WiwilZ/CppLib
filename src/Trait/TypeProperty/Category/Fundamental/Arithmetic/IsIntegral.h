//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Constant.h"
#include "../../../../../Macro.h"


#if __has_builtin(__is_integral)

template <typename T>
constexpr bool IsIntegral_V = __is_integral(T);

#elif defined(_MSC_VER)

template <typename T>
constexpr bool IsIntegral_V = IsAnyOf_V<RemoveCV_T<T>, bool, char, wchar_t, char8_t, char16_t, char32_t,
        signed char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;

#else

template <typename T>
constexpr bool IsIntegral_V = requires(T t, T* p, void f(T)) {
    reinterpret_cast<T>(t); // 排除类类型
    f(0); // 排除枚举类型
    p + t; // 排除所有尚未排除的类型
};

#endif // __has_builtin(__is_integral)


template <typename T>
struct IsIntegral : BoolConstant<IsIntegral_V<T>> {};
