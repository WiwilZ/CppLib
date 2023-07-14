//
// Created by WiwilZ on 2023/6/16.
//

#pragma once


/* MIPS 32-bit and 64-bit */
#if defined(mips) || defined(__mips__) || defined(MIPS) || defined(_MIPS_) || defined(__mips64)
#   if defined(_ABI64) && _MIPS_SIM == _ABI64
#       define ARCH_MIPS64 1
#   else
#       define ARCH_MIPS 1
#   endif
#endif


/* PowerPC 64-bit Big Endian */
#if (defined(__ppc64__) || defined(__PPC64__)) && defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define ARCH_PPC64 1
#   define ARCH_BIG_ENDIAN 1
#endif


/* PowerPC 64-bit Little Endian */
#if (defined(__ppc64__) || defined(__PPC64__) || defined(__ppc64le__) || defined(__PPC64LE__)) && defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#   define ARCH_PPC64LE 1
#endif


/* PowerPC 32-bit */
#if (defined(__ppc__) || defined(__PPC__) || defined(__PPC) || defined(__powerpc__) || defined(__powerpc) || defined(__POWERPC__) || defined(_M_PPC)) && !defined(ARCH_PPC64) && defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define ARCH_PPC 1
#endif


/* i386 / x86 32-bit */
#if defined(__i386__) || defined(i386) || defined(_M_IX86) || defined(_X86_) || defined(__THW_INTEL)
#   define ARCH_X86 1
#endif


/* AMD64 / Intel64 / x86_64 64-bit */
#if defined(__x86_64__) || defined(_M_X64)
#   define ARCH_X86_64 1
#endif


/* arm64 */
#if defined(__arm64__)|| defined(__aarch64__) || defined(_M_ARM64)
#   define ARCH_ARM64 1
#   ifdef __arm64e__
#       define ARCH_ARM64E 1
#   endif
#endif

/* arm */
#if defined(arm) || defined(__arm__) || defined(ARM) || defined(_ARM_) || defined(_M_ARM)
#   define ARCH_ARM 1

#   if defined(__ARM_ARCH_4__) || defined(__ARM_ARCH_4T__) || defined(__MARM_ARMV4__)
#       define ARM_ARCH_VERSION 4
#   elif defined(__ARM_ARCH_5__) || defined(__ARM_ARCH_5T__) || defined(__MARM_ARMV5__)
#       define ARM_ARCH_VERSION 5
#   elif defined(__ARM_ARCH_5E__) || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)
#       define ARM_ARCH_VERSION 5
#   elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__) || defined(__ARMV6__)
#       define ARM_ARCH_VERSION 6
#   elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7K__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7S__)
#       define ARM_ARCH_VERSION 7
#   elif defined(__ARM_ARCH_8__) || defined(__ARM_ARCH_8A__)
#       define ARM_ARCH_VERSION 8
/* MSVC sets _M_ARM */
#   elif defined(_M_ARM)
#       define ARM_ARCH_VERSION _M_ARM
/* RVCT sets _TARGET_ARCH_ARM */
#   elif defined(__TARGET_ARCH_ARM)
#       define ARM_ARCH_VERSION __TARGET_ARCH_ARM
#   else
#       define ARM_ARCH_VERSION 0
#   endif

#   ifdef __ARM_PCS_VFP
#       define ARCH_ARM_HARDFP 1
#   endif

#   if defined(__VFP_FP__) && !defined(__SOFTFP__)
#       define ARCH_ARM_VFP 1
#   endif

#   ifdef __ARM_NEON__
#       define ARCH_ARM_NEON 1
#       define ARCH_ARM_VFP_V3_D32 1
#   else
#       define ARCH_ARM_VFP_V2 1
#   endif

#   ifdef __ARM_ARCH_7K__
#       define ARCH_APPLE_ARMV7K 1
#   endif

#   ifdef __ARM_ARCH_7S__
#       define WTF_ARCH_APPLE_ARMV7S 1
#   endif
#endif

