//
// Created by WiwilZ on 2023/6/16.
//

#pragma once



/* Windows */
#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_)
#   define OS_WINDOWS 1
#   if defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#       define OS_WIN64 1
#   else
#       define OS_WIN32 1
#   endif
#endif



/* AIX */
#ifdef _AIX
#   define OS_AIX 1
#endif


/* Fuchsia */
#ifdef __Fuchsia__
#   define OS_FUCHSIA 1
#endif


/* GNU/Hurd */
#ifdef __GNU__
#   define OS_HURD 1
#endif


/* Solaris */
#if defined(sun) || defined(__sun)
#   define OS_SOLARIS 1
#endif


/* Linux */
#ifdef __linux__
#   define OS_LINUX 1
#endif


/* Android */
#ifdef __ANDROID__
#   define OS_ANDROID 1
#endif


/* Any Darwin-based OS, including macOS, iOS, macCatalyst, tvOS, and watchOS */
#ifdef __APPLE__
#   define OS_DARWIN 1
#include <Availability.h>
#include <AvailabilityMacros.h>
#include <TargetConditionals.h>
/* iOS family, including iOS, iPadOS, macCatalyst, tvOS, watchOS */
#   if TARGET_OS_IPHONE
#       define OS_IOS_FAMILY 1
#   endif
/* iOS and iPadOS only (iPhone and iPad), not including macCatalyst, not including watchOS, not including tvOS */
#   if TARGET_OS_IOS && !(defined(TARGET_OS_MACCATALYST) && TARGET_OS_MACCATALYST)
#       define OS_IOS 1
#   endif
/* tvOS */
#   if TARGET_OS_TV
#       define OS_TVOS 1
#   endif
/* watchOS */
#   if TARGET_OS_WATCH
#       define OS_WATCHOS 1
#   endif
/* macOS */
#   if TARGET_OS_OSX
#       define OS_MACOS 1
#   endif
#endif


/* FreeBSD */
#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#   define OS_FREEBSD 1
#endif


/* NetBSD */
#ifdef __NetBSD__
#   define OS_NETBSD 1
#endif


/* OpenBSD */
#ifdef __OpenBSD__
#   define OS_OPENBSD 1
#endif



/* Any Unix-like system */
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(OS_AIX) || defined(OS_HURD) || defined(OS_SOLARIS) || defined(OS_LINUX) || defined(OS_ANDROID) || defined(OS_DARWIN) || defined(OS_FREEBSD) || defined(OS_NETBSD) || defined(OS_OPENBSD)
#   define OS_UNIX 1
#endif

