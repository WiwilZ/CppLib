//
// Created by WiwilZ on 2023/5/29.
//

#pragma once


#if defined(__clang__)
    #define CLANG_COMPILER
#endif

#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
    #define GCC_COMPILER
#endif

#ifdef _MSC_VER
    #define MSVC_COMPILER
#endif


#ifndef __has_builtin
    #define __has_builtin(x) 0
#endif


#if __has_cpp_attribute(assume)
#define ASSUME(x) [[assume(x)]]
#elif defined(__clang__)
#define ASSUME(x) __builtin_assume(x)
#elif defined(__GNUC__)
#define ASSUME(x) __attribute__((assume(x)))
#elif defined(_MSC_VER)
#define ASSUME(x) __assume(x)
#else
#define ASSUME(x)
#endif


#if defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline
#endif

