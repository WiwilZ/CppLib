//
// Created by WiwilZ on 2023/6/5.
//

#pragma once


#ifdef __GUNC__
enum class Endian {
    Little = __ORDER_LITTLE_ENDIAN__,
    Big    = __ORDER_BIG_ENDIAN__,
    Middle = __ORDER_PDP_ENDIAN__,
    Native = __BYTE_ORDER__
};
#elif defined(WIN32) || defined(_WIN32) || defined(_WIN32_)
enum class Endian {
    Little = 1234,
    Big    = 4321,
    Middle = 3412,
    Native = Little
};
#else
#include <sys/types.h>
#   if __has_include(<endian.h>)
#include <endian.h>
enum class Endian {
    Little = __LITTLE_ENDIAN,
    Big    = __BIG_ENDIAN,
    Middle = __PDP_ENDIAN,
    Native = __BYTE_ORDER
};
#   else
#       if __has_include(<machine/endian.h>)
#include <machine/endian.h>
#       elif __has_include(<sys/endian.h>)
#include <sys/endian.h>
#       else
#error "Unsupported endian"
#       endif
enum class Endian {
    Little = LITTLE_ENDIAN,
    Big    = BIG_ENDIAN,
    Middle = PDP_ENDIAN,
    Native = BYTE_ORDER
};
#   endif
#endif
