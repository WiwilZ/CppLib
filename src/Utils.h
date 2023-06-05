//
// Created by WiwilZ on 2023/5/29.
//

#pragma once


#include "Macro.h"


#if defined(__GNUC__) || defined(__clang__)
#include "Trait/TypeProperty/Property/IsTriviallyCopyable.h"
#include "Trait/TypeProperty/Category/Compound/IsPointer.h"


namespace Detail {
    template <typename T>
    concept InRegister = IsTriviallyCopyable_V<T> && sizeof(T) <= sizeof(T*) && !IsPointer_V<T>;

    template <typename T>
    concept InMemory = !InRegister<T>;
}

FORCEINLINE void DoNotOptimize(const Detail::InRegister auto& x) noexcept {
    asm volatile("" : : "r"(x));
}

FORCEINLINE void DoNotOptimize(const Detail::InMemory auto& x) noexcept {
    asm volatile("" : : "m"(x) : "memory");
}

#else

namespace internal {
#pragma optimize("", off)
    inline void DoNotOptimizeImpl(const void*) noexcept {}
#pragma optimize("", on)
}

FORCEINLINE void DoNotOptimize(const auto& x) noexcept {
    internal::DoNotOptimizeImpl(&x);
}

#endif