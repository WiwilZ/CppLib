//
// Created by WiwilZ on 2023/6/3.
//

#pragma once

#include "../../Constant.h"


#if __has_builtin(__is_corresponding_member) || defined(_MSC_VER) && !defined(__clang__)

template <typename ClassTy1, typename MemberTy1, typename ClassTy2, typename MemberTy2>
[[nodiscard]] constexpr bool IsCorrespondingMember(MemberTy1 ClassTy1::* m1, MemberTy2 ClassTy2::* m2) noexcept {
    return __is_corresponding_member(ClassTy1, ClassTy2, m1, m2);
}

#elif __has_builtin(__builtin_is_corresponding_member)

template <typename ClassTy1, typename MemberTy1, typename ClassTy2, typename MemberTy2>
[[nodiscard]] constexpr bool IsCorrespondingMember(MemberTy1 ClassTy1::* m1, MemberTy2 ClassTy2::* m2) noexcept {
    return __builtin_is_corresponding_member(m1, m2);
}

#endif // __has_builtin(__is_corresponding_member) || defined(_MSC_VER) && !defined(__clang__)
