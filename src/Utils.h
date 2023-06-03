//
// Created by WiwilZ on 2023/5/29.
//

#pragma once

#include "Macro.h"
#include <concepts>


[[noreturn]] FORCE_INLINE void Unreachable() {
#if defined(__GNUC__) || defined(__clang__)
    __builtin_unreachable();
#elif defined(_MSC_VER)
    __assume(false);
#endif
}


#if defined(__GNUC__) || defined(__clang__)

namespace internal {
    template <typename T>
    concept from_register = std::is_trivially_copyable_v<T> && sizeof(T) <= sizeof(T*) && !std::is_pointer_v<T>;

    template <typename T>
    concept from_memory = !from_register<T>;
}

FORCE_INLINE void DoNotOptimize(const internal::from_register auto& t) noexcept {
    asm volatile("" : : "r"(t));
}

FORCE_INLINE void DoNotOptimize(const internal::from_memory auto& t) noexcept {
    asm volatile("" : : "m"(t) : "memory");
}

#elif defined(_MSC_VER)

namespace internal {
#pragma optimize("", off)
    inline void DoNotOptimizeImpl(const void*) noexcept {}
#pragma optimize("", on)
}

FORCE_INLINE void DoNotOptimize(const auto& t) noexcept {
    internal::DoNotOptimizeImpl(&t);
}

#endif