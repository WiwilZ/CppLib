//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__is_pointer_interconvertible_with_class) || defined(_MSC_VER) && !defined(__clang__)

namespace Trait {

    template <typename ClassTy, typename MemberTy>
    [[nodiscard]] constexpr bool IsPointerInterconvertibleWithClass(MemberTy ClassTy::* mp) noexcept {
        return __is_pointer_interconvertible_with_class(ClassTy, mp);
    }

} // namespace Trait

#elif __has_builtin(__builtin_is_pointer_interconvertible_with_class)

namespace Trait {

    template <typename ClassTy, typename MemberTy>
    [[nodiscard]] constexpr bool IsPointerInterconvertibleWithClass(MemberTy ClassTy::* mp) noexcept {
        return __builtin_is_pointer_interconvertible_with_class(mp);
    }

} // namespace Trait

#endif
