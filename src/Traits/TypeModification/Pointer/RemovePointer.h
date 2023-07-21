//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


namespace traits {
    template <typename T>
    struct RemovePointer {
        using Type = T;
    };

    template <typename T>
    struct RemovePointer<T *> {
        using Type = T;
    };

    template <typename T>
    struct RemovePointer<const T*> {
        using Type = T;
    };

    template <typename T>
    struct RemovePointer<volatile T*> {
        using Type = T;
    };

    template <typename T>
    struct RemovePointer<const volatile T*> {
        using Type = T;
    };


    template <typename T>
    using RemovePointer_T = typename RemovePointer<T>::Type;
}

