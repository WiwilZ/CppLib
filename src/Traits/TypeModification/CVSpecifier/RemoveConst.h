//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


namespace traits {

    template <typename T>
    struct RemoveConst {
        using Type = T;
    };

    template <typename T>
    struct RemoveConst<const T> {
        using Type = T;
    };


    template <typename T>
    using RemoveConst_T = typename RemoveConst<T>::Type;

} // namespace traits
