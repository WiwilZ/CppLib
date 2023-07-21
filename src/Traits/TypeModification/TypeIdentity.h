//
// Created by WiwilZ on 2023/5/28.
//

#pragma once


namespace traits {

    template <typename T>
    struct TypeIdentity {
        using Type = T;
    };

} // namespace traits
