//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include <cstddef>
#include "../Macro.h"


namespace Trait {
    template <typename T, T... Es>
    struct ConstantList {
        using Type = ConstantList;
        using ElementType = T;
        static constexpr std::size_t Length = sizeof...(Es);
    };
}


#if HAS_BUILTIN(__make_integer_seq) || defined(_MSC_VER)
namespace Trait {

    template <typename T, std::size_t N>
    using MakeIntegerSequence = __make_integer_seq<ConstantList, T, N>;

} // namespace Trait
#elif HAS_BUILTIN(__integer_pack)
namespace Trait {

    template <typename T, std::size_t N>
    using MakeIntegerSequence = ConstantList<T, __integer_pack(N)...>;

} // namespace Trait
#else // !HAS_BUILTIN(__make_integer_seq) && !HAS_BUILTIN(__integer_pack)
namespace Trait {
    namespace Detail {
        template <typename Seq, bool IsOdd>
        struct ExtendSequence;

        template <typename T, T... Is>
        struct ExtendSequence<ConstantList<T, Is...>, false> : ConstantList<T, Is..., (sizeof...(Is) + Is)...> {};

        template <typename T, T... Is>
        struct ExtendSequence<ConstantList<T, Is...>, true> : ConstantList<T, Is..., (sizeof...(Is) + Is)..., 2 * sizeof...(Is)> {};
    }


    template <typename T, std::size_t N>
    struct MakeIntegerSequence : Detail::ExtendSequence<typename MakeIntegerSequence<T, N / 2>::Type, N & 1> {};

    template <typename T>
    struct MakeIntegerSequence<T, 0> : ConstantList<T> {};

    template <typename T>
    struct MakeIntegerSequence<T, 1> : ConstantList<T, 0> {};
}
#endif


namespace Trait {
    template <std::size_t N>
    using MakeIndexSequence = MakeIntegerSequence<std::size_t, N>;


    template <typename... Ts>
    using IndexSequenceFor = MakeIndexSequence<sizeof...(Ts)>;
}
