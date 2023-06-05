//
// Created by WiwilZ on 2023/6/5.
//

#pragma once

#include "SignedIntegerType.h"
#include "UnsignedIntegerType.h"


template <typename T>
concept IntegerType = SignedIntegerType<T> || UnsignedIntegerType<T>;
