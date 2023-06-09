//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "../Reference/RemoveReference.h"
#include "../Void_T.h"


namespace Trait {

    namespace Detail {

        template <typename T, typename = void>
        struct AddPointer {
            using Type = T;
        };

        template <typename T>
        struct AddPointer<T, Void_T<RemoveReference_T<T>*>> {
            using Type = RemoveReference_T<T>*;
        };

    } // namespace Detail


    template <typename T>
    struct AddPointer {
        using Type = typename Detail::AddPointer<T>::Type;
    };


    template <typename T>
    using AddPointer_T = typename AddPointer<T>::Type;

} // namespace Trait
