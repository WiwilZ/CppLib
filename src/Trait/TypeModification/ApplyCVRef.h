//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "CVSpecifier/ApplyCV.h"
#include "RemoveCVRef.h"
#include "Reference/RemoveReference.h"
#include "Reference/ApplyReference.h"


template <typename From, typename To>
using ApplyCVRef_T = ApplyReference_T<From, ApplyCV_T<From, RemoveCVRef_T<To>>>;


template <typename From, typename To>
struct ApplyCVRef {
    using Type = ApplyCVRef_T<From, To>;
};
