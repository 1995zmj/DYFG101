

#pragma once

#include "GameplayEffectTypes.h"

#include "G01GameplayEffectContext.generated.h"

class AActor;
class FArchive;
class IG01AbilitySourceInterface;
class UObject;
class UPhysicalMaterial;

USTRUCT()
struct FG01GameplayEffectContext: public FGameplayEffectContext
{
	GENERATED_BODY()

	FG01GameplayEffectContext()
		: FGameplayEffectContext()
	{
	}

	FG01GameplayEffectContext(AActor* InInstigator, AActor* InEffectCauser)
		: FGameplayEffectContext(InInstigator, InEffectCauser)
	{
	}

	/** Returns the wrapped FLyraGameplayEffectContext from the handle, or nullptr if it doesn't exist or is the wrong type */
	static FG01GameplayEffectContext* ExtractEffectContext(struct FGameplayEffectContextHandle Handle);

	/** Sets the object used as the ability source */
	void SetAbilitySource(const IG01AbilitySourceInterface* InObject, float InSourceLevel);

	/** Returns the ability source interface associated with the source object. Only valid on the authority. */
	const IG01AbilitySourceInterface* GetAbilitySource() const;

	//virtual FGameplayEffectContext* Duplicate() const override
	//{
	//	FG01GameplayEffectContext* NewContext = new FG01GameplayEffectContext();
	//	*NewContext = *this;
	//	if (GetHitResult())
	//	{
	//		// Does a deep copy of the hit result
	//		NewContext->AddHitResult(*GetHitResult(), true);
	//	}
	//	return NewContext;
	//}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FG01GameplayEffectContext::StaticStruct();
	}

	/** Overridden to serialize new fields */
	//virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	/** Returns the physical material from the hit result if there is one */
	const UPhysicalMaterial* GetPhysicalMaterial() const;

public:
	/** ID to allow the identification of multiple bullets that were part of the same cartridge */
	UPROPERTY()
	int32 CartridgeID = -1;

protected:
	/** Ability Source object (should implement ILyraAbilitySourceInterface). NOT replicated currently */
	UPROPERTY()
	TWeakObjectPtr<const UObject> AbilitySourceObject;
};


//template<>
//struct TStructOpsTypeTraits<FG01GameplayEffectContext> : public TStructOpsTypeTraitsBase2<FG01GameplayEffectContext>
//{
//	enum
//	{
//		WithNetSerializer = true,
//		WithCopy = true
//	};
//};
