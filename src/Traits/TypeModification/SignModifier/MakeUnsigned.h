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
        constexpr auto MakeUnsignedHelper() noexcept {
            if constexpr (sizeof(T) == 1) {
                return TypeIdentity<unsigned char>{};
            } else if constexpr (sizeof(T) == 2) {
                return TypeIdentity<unsigned short>{};
            } else if constexpr (sizeof(T) == 4) {
                if constexpr (IsSame_V<T, int> || IsSame_V<T, unsigned int>) {
                    return TypeIdentity<unsigned int>{};
                } else if constexpr (IsSame_V<T, long> || IsSame_V<T, unsigned long>) {
                    return TypeIdentity<unsigned long>{};
                } else {
                    return TypeIdentity<u32>{};
                }
            } else if constexpr (sizeof(T) == 8) {
                if constexpr (IsSame_V<T, long> || IsSame_V<T, unsigned long>) {
                    return TypeIdentity<unsigned long>{};
                } else if constexpr (IsSame_V<T, long long> || IsSame_V<T, unsigned long long>) {
                    return TypeIdentity<unsigned long long>{};
                } else {
                    return TypeIdentity<u64>{};
                }
            } else {
#if HAS_INT128
                static_assert(sizeof(T) <= 16, "Unexpected integral or enum size");
                return TypeIdentity<u128>{};
#else
                static_assert(sizeof(T) <= 8, "Unexpected integral or enum size");
#endif
            }
        }
    }


    template <typename T>
    requires (IsIntegral_V<T> && !IsSame_V<RemoveCV_T<T>, bool> || IsEnum_V<T>)
    struct MakeUnsigned {
        using Type = ApplyCV_T<T, typename decltype(detail::MakeUnsignedHelper<RemoveCV_T<T>>())::Type>;
    };


    template <typename T>
    requires (IsIntegral_V<T> && !IsSame_V<RemoveCV_T<T>, bool> || IsEnum_V<T>)
    using MakeUnsigned_T = typename MakeUnsigned<T>::Type;
}

