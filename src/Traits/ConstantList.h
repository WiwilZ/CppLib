//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "../ArithmeticType.h"
#include "../Macro.h"


namespace traits {
    template <typename T, T... Es>
    struct ConstantList {
        using Type = ConstantList;
        using ElementType = T;
        static constexpr usize Length = sizeof...(Es);
    };
}


#if HAS_BUILTIN(__make_integer_seq) || defined(_MSC_VER)
namespace traits {
    template <typename T, usize N>
    using MakeIntegerSequence = __make_integer_seq<ConstantList, T, N>;
}
#elif HAS_BUILTIN(__integer_pack)
namespace traits {
    template <typename T, usize N>
    using MakeIntegerSequence = ConstantList<T, __integer_pack(N)...>;
}
#else // !HAS_BUILTIN(__make_integer_seq) && !HAS_BUILTIN(__integer_pack)
namespace traits {
    namespace detail {
        template <typename Seq, bool IsOdd>
        struct ExtendSequence;

        template <typename T, T... Is>
        struct ExtendSequence<ConstantList<T, Is...>, false> : ConstantList<T, Is..., (sizeof...(Is) + Is)...> {};

        template <typename T, T... Is>
        struct ExtendSequence<ConstantList<T, Is...>, true> : ConstantList<T, Is..., (sizeof...(Is) + Is)..., 2 * sizeof...(Is)> {};
    }

    template <typename T, usize N>
    struct MakeIntegerSequence : detail::ExtendSequence<typename MakeIntegerSequence<T, N / 2>::Type, N & 1> {};

    template <typename T>
    struct MakeIntegerSequence<T, 0> : ConstantList<T> {};

    template <typename T>
    struct MakeIntegerSequence<T, 1> : ConstantList<T, 0> {};
}
#endif


namespace traits {
    template <usize N>
    using MakeIndexSequence = MakeIntegerSequence<usize, N>;


    template <typename... Ts>
    using IndexSequenceFor = MakeIndexSequence<sizeof...(Ts)>;
}
