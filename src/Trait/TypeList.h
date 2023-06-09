//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include <cstddef>


namespace Trait {
    template <typename... Ts>
    struct TypeList {
        static constexpr std::size_t Length = sizeof...(Ts);
    };
}

