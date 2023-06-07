//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


namespace Trait {

    template <typename T>
    struct RemoveReference {
        using Type = T;
    };

    template <typename T>
    struct RemoveReference<T&> {
        using Type = T;
    };

    template <typename T>
    struct RemoveReference<T&&> {
        using Type = T;
    };


    template <typename T>
    using RemoveReference_T = typename RemoveReference<T>::Type;

} // namespace Trait

