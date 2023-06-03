//
// Created by WiwilZ on 2023/5/28.
//

#pragma once

#include "Trait/Constant.h"
#include "Trait/ConstantList.h"
#include "Trait/DeclVal.h"
#include "Trait/FloatingPointTrait.h"
#include "Trait/IntegralTrait.h"
#include "Trait/IntegralType.h"
#include "Trait/LogicalOperation/Conjunction.h"
#include "Trait/LogicalOperation/Disjunction.h"
#include "Trait/LogicalOperation/Negation.h"
#include "Trait/TypeList.h"
#include "Trait/TypeModification/ApplyCVRef.h"
#include "Trait/TypeModification/Array/RemoveAllExtents.h"
#include "Trait/TypeModification/Array/RemoveExtent.h"
#include "Trait/TypeModification/CommonType.h"
#include "Trait/TypeModification/Conditional.h"
#include "Trait/TypeModification/CVSpecifier/ApplyCV.h"
#include "Trait/TypeModification/CVSpecifier/RemoveConst.h"
#include "Trait/TypeModification/CVSpecifier/RemoveCV.h"
#include "Trait/TypeModification/CVSpecifier/RemoveVolatile.h"
#include "Trait/TypeModification/Decay.h"
#include "Trait/TypeModification/Pointer/AddPointer.h"
#include "Trait/TypeModification/Pointer/RemovePointer.h"
#include "Trait/TypeModification/Reference/AddLValueReference.h"
#include "Trait/TypeModification/Reference/AddRValueReference.h"
#include "Trait/TypeModification/Reference/ApplyReference.h"
#include "Trait/TypeModification/Reference/MakeLValueReference.h"
#include "Trait/TypeModification/Reference/MakeRValueReference.h"
#include "Trait/TypeModification/Reference/RemoveReference.h"
#include "Trait/TypeModification/RemoveCVRef.h"
#include "Trait/TypeModification/SignModifier/MakeSigned.h"
#include "Trait/TypeModification/SignModifier/MakeUnsigned.h"
#include "Trait/TypeModification/TypeIdentity.h"
#include "Trait/TypeModification/UnderlyingType.h"
#include "Trait/TypeModification/Void_T.h"
#include "Trait/TypeProperty/Category/Compound/Array/IsBoundedArray.h"
#include "Trait/TypeProperty/Category/Compound/Array/IsUnboundedArray.h"
#include "Trait/TypeProperty/Category/Compound/Enum/IsScopedEnum.h"
#include "Trait/TypeProperty/Category/Compound/IsArray.h"
#include "Trait/TypeProperty/Category/Compound/IsClass.h"
#include "Trait/TypeProperty/Category/Compound/IsClassOrUnion.h"
#include "Trait/TypeProperty/Category/Compound/IsEnum.h"
#include "Trait/TypeProperty/Category/Compound/IsFunction.h"
#include "Trait/TypeProperty/Category/Compound/IsMemberPointer.h"
#include "Trait/TypeProperty/Category/Compound/IsPointer.h"
#include "Trait/TypeProperty/Category/Compound/IsReference.h"
#include "Trait/TypeProperty/Category/Compound/IsUnion.h"
#include "Trait/TypeProperty/Category/Compound/MemberPointer/IsMemberFunctionPointer.h"
#include "Trait/TypeProperty/Category/Compound/MemberPointer/IsMemberObjectPointer.h"
#include "Trait/TypeProperty/Category/Compound/Pointer/IsFunctionPointer.h"
#include "Trait/TypeProperty/Category/Compound/Pointer/IsObjectPointer.h"
#include "Trait/TypeProperty/Category/Compound/Reference/IsLValueReference.h"
#include "Trait/TypeProperty/Category/Compound/Reference/IsRValueReference.h"
#include "Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/IsSignedIntegral.h"
#include "Trait/TypeProperty/Category/Fundamental/Arithmetic/Integral/IsUnsignedIntegral.h"
#include "Trait/TypeProperty/Category/Fundamental/Arithmetic/IsFloatingPoint.h"
#include "Trait/TypeProperty/Category/Fundamental/Arithmetic/IsIntegral.h"
#include "Trait/TypeProperty/Category/Fundamental/IsArithmetic.h"
#include "Trait/TypeProperty/Category/Fundamental/IsNullPointer.h"
#include "Trait/TypeProperty/Category/Fundamental/IsVoid.h"
#include "Trait/TypeProperty/Category/IsCompleteVoidOrUnboundedArray.h"
#include "Trait/TypeProperty/Category/IsCompound.h"
#include "Trait/TypeProperty/Category/IsFundamental.h"
#include "Trait/TypeProperty/Category/IsObject.h"
#include "Trait/TypeProperty/Category/IsScalar.h"
#include "Trait/TypeProperty/Category/IsTrivial.h"
#include "Trait/TypeProperty/Property/HasUniqueObjectRepresentations.h"
#include "Trait/TypeProperty/Property/IsAbstract.h"
#include "Trait/TypeProperty/Property/IsAggregate.h"
#include "Trait/TypeProperty/Property/IsConst.h"
#include "Trait/TypeProperty/Property/IsEmpty.h"
#include "Trait/TypeProperty/Property/IsFinal.h"
#include "Trait/TypeProperty/Property/IsPolymorphic.h"
#include "Trait/TypeProperty/Property/IsReferencable.h"
#include "Trait/TypeProperty/Property/IsStandardLayout.h"
#include "Trait/TypeProperty/Property/IsTriviallyCopyable.h"
#include "Trait/TypeProperty/Property/IsVolatile.h"
#include "Trait/TypeProperty/PropertyQuery/AlignmentOf.h"
#include "Trait/TypeProperty/PropertyQuery/Extent.h"
#include "Trait/TypeProperty/PropertyQuery/Rank.h"
#include "Trait/TypeProperty/Relationship/IsAnyOf.h"
#include "Trait/TypeProperty/Relationship/IsBaseOf.h"
#include "Trait/TypeProperty/Relationship/IsConvertible.h"
#include "Trait/TypeProperty/Relationship/IsCorrespondingMember.h"
#include "Trait/TypeProperty/Relationship/IsLayoutCompatible.h"
#include "Trait/TypeProperty/Relationship/IsNothrowConvertible.h"
#include "Trait/TypeProperty/Relationship/IsPointerInterconvertibleBaseOf.h"
#include "Trait/TypeProperty/Relationship/IsPointerInterconvertibleWithClass.h"
#include "Trait/TypeProperty/Relationship/IsSame.h"
#include "Trait/TypeProperty/Relationship/ReferenceConstructsFromTemporary.h"
#include "Trait/TypeProperty/Relationship/ReferenceConvertsFromTemporary.h"
#include "Trait/TypeProperty/SupportedOperation/Assignable/IsAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/Assignable/IsNothrowAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/Assignable/IsTriviallyAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/Constructible/IsConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/Constructible/IsNothrowConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/Constructible/IsTriviallyConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/CopyAssignable/IsCopyAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/CopyAssignable/IsNothrowCopyAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/CopyAssignable/IsTriviallyCopyAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/CopyConstructible/IsCopyConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/CopyConstructible/IsNothrowCopyConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/CopyConstructible/IsTriviallyCopyConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/DefaultConstructible/IsDefaultConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/DefaultConstructible/IsNothrowDefaultConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/DefaultConstructible/IsTriviallyDefaultConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/Destructible/IsDestructible.h"
#include "Trait/TypeProperty/SupportedOperation/Destructible/IsNothrowDestructible.h"
#include "Trait/TypeProperty/SupportedOperation/Destructible/IsTriviallyDestructible.h"
#include "Trait/TypeProperty/SupportedOperation/HasVirtualDestructor.h"
#include "Trait/TypeProperty/SupportedOperation/MoveAssignable/IsMoveAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/MoveAssignable/IsNothrowMoveAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/MoveAssignable/IsTriviallyMoveAssignable.h"
#include "Trait/TypeProperty/SupportedOperation/MoveConstructible/IsMoveConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/MoveConstructible/IsNothrowMoveConstructible.h"
#include "Trait/TypeProperty/SupportedOperation/MoveConstructible/IsTriviallyMoveConstructible.h"

