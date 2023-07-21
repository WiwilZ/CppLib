//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../../ArithmeticType.h"
#include "../../TypeProperty/Category/Fundamental/Arithmetic/IsIntegral.h"
#include "../../TypeProperty/Category/Compound/IsEnum.h"
#include "../../TypeProperty/Relationship/IsSame.h"
#include "../CVSpecifier/ApplyCV.h"
#include "../CVSpecifier/RemoveCV.h"
#include "../TypeIdentity.h"


namespace traits {
    namespace detail {
        template <typename T>
        constexpr auto MakeSignedHelper() noexcept {
            if constexpr (sizeof(T) == 1) {
                return TypeIdentity<signed char>{};
            } else if constexpr (sizeof(T) == 2) {
                return TypeIdentity<short>{};
            } else if constexpr (sizeof(T) == 4) {
                if constexpr (IsSame_V<T, int> || IsSame_V<T, unsigned int>) {
                    return TypeIdentity<int>{};
                } else if constexpr (IsSame_V<T, long> || IsSame_V<T, unsigned long>) {
                    return TypeIdentity<long>{};
                } else {
                    return TypeIdentity<i32>{};
                }
            } else if constexpr (sizeof(T) == 8) {
                if constexpr (IsSame_V<T, long> || IsSame_V<T, unsigned long>) {
                    return TypeIdentity<long> {};
                } else if constexpr (IsSame_V<T, long long> || IsSame_V<T, unsigned long long>) {
                    return TypeIdentity<long long>{};
                } else {
                    return TypeIdentity<i64>{};
                }
            } else {
#if HAS_INT128
                static_assert(sizeof(T) <= 16, "Unexpected integral or enum size");
                return TypeIdentity<i128>{};
#else
                static_assert(sizeof(T) <= 8, "Unexpected integral or enum size");
#endif
            }
        }
    }


    template <typename T>
    requires (IsIntegral_V<T> && !IsSame_V<RemoveCV_T<T>, bool> || IsEnum_V<T>)
    struct MakeSigned {
        using Type = ApplyCV_T<T, typename decltype(detail::MakeSignedHelper<RemoveCV_T<T>>())::Type>;
    };


    template <typename T>
    requires (IsIntegral_V<T> && !IsSame_V<RemoveCV_T<T>, bool> || IsEnum_V<T>)
    using MakeSigned_T = typename MakeSigned<T>::Type;
}

