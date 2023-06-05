//
// Created by WiwilZ on 2023/6/5.
//

#pragma once


enum class Endian {
#ifdef _WIN32
    Little = 0,
    Big    = 1,
    Native = Little
#else
    Little = __ORDER_LITTLE_ENDIAN__,
    Big    = __ORDER_BIG_ENDIAN__,
    Native = __BYTE_ORDER__
#endif
};
