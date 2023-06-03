//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../../Macro.h"
#include "../../../../Constant.h"


#if __has_builtin(__is_integral)

template <typename T>
constexpr bool IsIntegral_V = __is_integral(T);

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
