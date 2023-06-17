//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "Macro.h"


#if defined(_MSC_VER) && !defined(__clang__)
namespace Detail {
#pragma optimize("", off)
    inline void DoNotOptimizeImpl(const void*) noexcept {}
#pragma optimize("", on)
}

__forceinline void DoNotOptimize(const auto& x) noexcept {
    Detail::DoNotOptimizeImpl(&x);
}
#else // !(defined(_MSC_VER) && !defined(__clang__))
#include "Trait/TypeProperty/Property/IsTriviallyCopyable.h"
#include "Trait/TypeProperty/Category/Compound/IsPointer.h"


namespace Detail {
    template <typename T>
    concept InRegister = Trait::IsTriviallyCopyable_V<T> && sizeof(T) <= sizeof(T*) && !Trait::IsPointer_V<T>;

    template <typename T>
    concept InMemory = !InRegister<T>;
} // namespace Detail


ALWAYS_INLINE void DoNotOptimize(const Detail::InRegister auto& x) noexcept {
    asm volatile("" : : "r"(x));
}

ALWAYS_INLINE void DoNotOptimize(const Detail::InMemory auto& x) noexcept {
    asm volatile("" : : "m"(x) : "memory");
}
#endif
