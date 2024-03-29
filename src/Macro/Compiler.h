//
// Created by 99728 on 2023/6/16.
//

#pragma once


#ifdef __has_builtin
#   define HAS_BUILTIN(x) __has_builtin(x)
#else
#   define HAS_BUILTIN(x) 0
#endif

#ifdef __has_attribute
#   define HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#   define HAS_ATTRIBUTE(x) 0
#endif

#ifdef __has_feature
#   define HAS_FEATURE(x) __has_feature(x)
#else
#   define HAS_FEATURE(x) 0
#endif

#ifdef __has_declspec_attribute
#   define HAS_DECLSPEC_ATTRIBUTE(x) __has_declspec_attribute(x)
#else
#   define HAS_DECLSPEC_ATTRIBUTE(x) 0
#endif




/* Clang  */
#ifdef __clang__
#   define COMPILER_CLANG 1
#   define CLANG_VERSION __clang_version__
#endif


/* GCC */
#ifdef __GNUC__
#   define COMPILER_COMPATIBLE_GCC 1
#   ifndef __clang__
#       define COMPILER_GCC 1
#       define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#   endif
#endif


/* MSVC */
#ifdef _MSC_VER
#   define COMPILER_COMPATIBLE_MSVC 1
#   define MSVC_VERSION _MSC_FULL_VER
#   include <sal.h>
#   ifndef __clang__
#       define COMPILER_MSVC 1
#   endif
#endif


/* MinGW GCC */
#ifdef __MINGW32__
#   define COMPILER_MINGW 1
#   include <_mingw.h>
#endif


/* mingw-w64 GCC */
#ifdef __MINGW64__
#   define COMPILER_MINGW64 1
#endif




/* COMPILER_SUPPORTS(EABI) */
#if defined(__ARM_EABI__) || defined(__EABI__)
#   define SUPPORTS_EABI 1
#endif

/* ASAN_ENABLED and SUPPRESS_ASAN */
#ifdef __SANITIZE_ADDRESS__
#   define ASAN_ENABLED 1
#else
#   define ASAN_ENABLED HAS_FEATURE(address_sanitizer)
#endif

#if ASAN_ENABLED
#   define SUPPRESS_ASAN [[gnu::no_sanitize_address]]
#else
#   define SUPPRESS_ASAN
#endif


/* TSAN_ENABLED and SUPPRESS_TSAN */
#ifdef __SANITIZE_THREAD__
#define TSAN_ENABLED 1
#else
#define TSAN_ENABLED HAS_FEATURE(thread_sanitizer)
#endif

#if TSAN_ENABLED
#define SUPPRESS_TSAN [[gnu::no_sanitize_thread]]
#else
#define SUPPRESS_TSAN
#endif




/* ASSUME */
#if __has_cpp_attribute(assume)
#   define ASSUME(x) [[assume(x)]]
#elif defined(__clang__)
#   define ASSUME(x) __builtin_assume(x)
#elif defined(__GNUC__)
#   define ASSUME(x) __attribute__((assume(x)))
#elif defined(_MSC_VER)
#   define ASSUME(x) __assume(x)
#else
#   define ASSUME(x)
#endif


/* ALWAYS_INLINE */
#if defined(DEBUG) || defined(_DEBUG) || !(defined(NDEBUG) || defined(_NDEBUG))
#   define ALWAYS_INLINE
#elif defined(__GNUC__) && (defined(__clang__) || ASAN_ENABLED)
#   define ALWAYS_INLINE inline [[gnu::always_inline]]
#elif defined(_MSC_VER)
#   define ALWAYS_INLINE [[msvc::forceinline]]
#else
#   define ALWAYS_INLINE inline
#endif


/* NEVER_INLINE */
#ifdef __GNUC__
#   define NEVER_INLINE [[gnu::noinline]]
#elif defined(_MSC_VER)
#   define NEVER_INLINE [[msvc::noinline]]
#else
#   define NEVER_INLINE
#endif


/* NOT_TAIL_CALLED */
#if HAS_ATTRIBUTE(not_tail_called)
#   define NOT_TAIL_CALLED [[gnu::not_tail_called]]
#else
#   define NOT_TAIL_CALLED
#endif


/* RETURNS_NONNULL */
#ifdef __GNUC__
#   define RETURNS_NONNULL [[gnu::returns_nonnull]]
#elif defined(_MSC_VER)
#   define RETURNS_NONNULL _Ret_notnull_
#else
#   define RETURNS_NONNULL
#endif


/* PURE_FUNCTION */
#ifdef __GNUC__
#   define PURE_FUNCTION [[gnu::pure]]
#else
#   define PURE_FUNCTION
#endif


/* FLATTEN_FUNCTION */
#ifdef __GNUC__
#   define FLATTEN_FUNCTION [[gnu::flatten]]
#else
#   define FLATTEN_FUNCTION
#endif