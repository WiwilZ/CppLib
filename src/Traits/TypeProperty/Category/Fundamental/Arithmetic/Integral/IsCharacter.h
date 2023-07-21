//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../../../../Relationship/IsAnyOf.h"
#include "../../../../../TypeModification/CVSpecifier/RemoveCV.h"
#include "../../../../../Constant.h"


namespace traits {
    template <typename T>
    constexpr bool IsCharacter_V = IsAnyOf_V<RemoveCV_T<T>, char, wchar_t, char8_t, char16_t, char32_t>;


    template <typename T>
    struct IsCharacter : BoolConstant<IsCharacter_V<T>> {};
}
