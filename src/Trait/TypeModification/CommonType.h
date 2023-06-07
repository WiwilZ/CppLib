//
// Created by WiwilZ on 2023/5/30.
//

#pragma once

#include "Conditional.h"
#include "Decay.h"
#include "RemoveCVRef.h"
#include "Reference/RemoveReference.h"
#include "Reference/AddLValueReference.h"
#include "../DeclVal.h"
#include "../TypeProperty/Relationship/IsSame.h"
#include "Void_T.h"


namespace Trait {

    template <typename... T>
    struct CommonType {};

    template <typename T>
    struct CommonType<T> : CommonType<T, T> {};


    template <typename... T>
    using CommonType_T = typename CommonType<T...>::Type;


    namespace Detail {

        template <typename T1, typename T2>
        using CondResult_T = decltype(false ? Trait::DeclVal<T1>() : Trait::DeclVal<T2>());

        template <typename T1, typename T2, typename = void>
        struct DecayedCondResult {};

        template <typename T1, typename T2>
        struct DecayedCondResult<T1, T2, Void_T<CondResult_T<T1, T2>>> : Decay<CondResult_T<T1, T2>> {};


        template <typename T>
        using AddCRef_T = AddLValueReference_T<const RemoveReference_T<T>>;

        template <typename T1, typename T2, typename = void>
        struct DoubleCommonType : DecayedCondResult<AddCRef_T<T1>, AddCRef_T<T2>> {};

        template <typename T1, typename T2>
        struct DoubleCommonType<T1, T2, Void_T<CondResult_T<Decay_T<T1>, Decay_T<T2>>>>
                : DecayedCondResult<Decay_T<T1>, Decay_T<T2>> {
        };

    } // namespace Detail


    template <typename T1, typename T2>
    struct CommonType<T1, T2> : Conditional<IsSame_V<T1, Decay_T<T1>> && IsSame_V<T2, Decay_T<T2>>,
            typename Detail::DoubleCommonType<T1, T2>::Type,
            CommonType_T<Decay_T<T1>, Decay_T<T2>>> {};


    namespace Detail {

        template <typename AlwaysVoid, typename T1, typename T2, typename... R>
        struct MultiCommonType {};

        template <typename T1, typename T2, typename... R>
        struct MultiCommonType<Void_T<CommonType_T<T1, T2>>, T1, T2, R...> : CommonType<CommonType_T<T1, T2>, R...> {};

    } // namespace Detail


    template <typename T1, typename T2, typename... R>
    struct CommonType<T1, T2, R...> : Detail::MultiCommonType<void, T1, T2, R...> {};

} // namespace Trait


