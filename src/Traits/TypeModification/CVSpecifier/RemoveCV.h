//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


namespace traits {
    template <typename T>
    struct RemoveCV {
        using Type = T;
    };

    template <typename T>
    struct RemoveCV<const T> {
        using Type = T;
    };

    template <typename T>
    struct RemoveCV<volatile T> {
        using Type = T;
    };

    template <typename T>
    struct RemoveCV<const volatile T> {
        using Type = T;
    };


    template <typename T>
    using RemoveCV_T = typename RemoveCV<T>::Type;
}

