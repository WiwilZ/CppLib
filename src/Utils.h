//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "Macro.h"


#if defined(_MSC_VER) && !defined(__clang__)

namespace detail {
#pragma optimize("", off)
    inline void DoNotOptimizeImpl(const void*) noexcept {}
#pragma optimize("", on)
}

ALWAYS_INLINE void DoNotOptimize(const auto& x) noexcept {
    detail::DoNotOptimizeImpl(&x);
}

#else // !(defined(_MSC_VER) && !defined(__clang__))

#include "Traits/TypeProperty/Property/IsTriviallyCopyable.h"
#include "Traits/TypeProperty/Category/Compound/IsPointer.h"


namespace detail {
    template <typename T>
    concept InRegister = traits::IsTriviallyCopyable_V<T> && sizeof(T) <= sizeof(T*) && !traits::IsPointer_V<T>;

    template <typename T>
    concept InMemory = !InRegister<T>;
}


ALWAYS_INLINE void DoNotOptimize(const detail::InRegister auto& x) noexcept {
    asm volatile("" : : "r"(x));
}

ALWAYS_INLINE void DoNotOptimize(const detail::InMemory auto& x) noexcept {
    asm volatile("" : : "m"(x) : "memory");
}

#endif
