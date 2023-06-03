//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include <cstddef>
#include "../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../Relationship/IsSame.h"
#include "../../../Constant.h"


template <typename T>
constexpr bool IsNullPointer_V = IsSame_V<RemoveCV_T<T>, std::nullptr_t>;


template <typename T>
struct IsNullPointer : BoolConstant<IsNullPointer_V<T>> {};
