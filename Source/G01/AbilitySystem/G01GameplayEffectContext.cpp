#include "G01GameplayEffectContext.h"


#include "AbilitySystem/G01AbilitySourceInterface.h"
#include "Engine/HitResult.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

//#if UE_WITH_IRIS
//#include "Iris/ReplicationState/PropertyNetSerializerInfoRegistry.h"
//#include "Serialization/GameplayEffectContextNetSerializer.h"
//#endif

FG01GameplayEffectContext* FG01GameplayEffectContext::ExtractEffectContext(struct FGameplayEffectContextHandle Handle)
{
	FGameplayEffectContext* BaseEffectContext = Handle.Get();
	if ((BaseEffectContext != nullptr) && BaseEffectContext->GetScriptStruct()->IsChildOf(FG01GameplayEffectContext::StaticStruct()))
	{
		return (FG01GameplayEffectContext*)BaseEffectContext;
	}

	return nullptr;
}

//bool FG01GameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
//{
//	FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);
//
//	// Not serialized for post-activation use:
//	// CartridgeID
//
//	return true;
//}

//#if UE_WITH_IRIS
//namespace UE::Net
//{
//	// Forward to FGameplayEffectContextNetSerializer
//	// Note: If FLyraGameplayEffectContext::NetSerialize() is modified, a custom NetSerializesr must be implemented as the current fallback will no longer be sufficient.
//	UE_NET_IMPLEMENT_FORWARDING_NETSERIALIZER_AND_REGISTRY_DELEGATES(FG01GameplayEffectContext, FGameplayEffectContextNetSerializer);
//}
//#endif

void FG01GameplayEffectContext::SetAbilitySource(const IG01AbilitySourceInterface* InObject, float InSourceLevel)
{
	AbilitySourceObject = MakeWeakObjectPtr(Cast<const UObject>(InObject));
	//SourceLevel = InSourceLevel;
}

const IG01AbilitySourceInterface* FG01GameplayEffectContext::GetAbilitySource() const
{
	return Cast<IG01AbilitySourceInterface>(AbilitySourceObject.Get());
}

const UPhysicalMaterial* FG01GameplayEffectContext::GetPhysicalMaterial() const
{
	if (const FHitResult* HitResultPtr = GetHitResult())
	{
		return HitResultPtr->PhysMaterial.Get();
	}
	return nullptr;
}

