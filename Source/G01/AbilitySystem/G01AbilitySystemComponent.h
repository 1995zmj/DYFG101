

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"

#include "G01AbilitySystemComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_AbilityInputBlocked);

class UG01AbilityTagRelationshipMapping;
class UG01GameplayAbility;
/**
 * 
 */
UCLASS(MinimalAPI)
class UG01AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	UG01AbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	/** Sets the current tag relationship mapping, if null it will clear it out */
	void SetTagRelationshipMapping(UG01AbilityTagRelationshipMapping* NewMapping);


	typedef TFunctionRef<bool(const UG01GameplayAbility* LyraAbility, FGameplayAbilitySpecHandle Handle)> TShouldCancelAbilityFunc;
	void CancelAbilitiesByFunc(TShouldCancelAbilityFunc ShouldCancelFunc, bool bReplicateCancelAbility);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

protected:
	// If set, this table is used to look up tag relationships for activate and cancel
	UPROPERTY()
	TObjectPtr<UG01AbilityTagRelationshipMapping> TagRelationshipMapping;

	// Handles to abilities that had their input pressed this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// Handles to abilities that have their input held.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	// Number of abilities running in each activation group.
	//int32 ActivationGroupCounts[(uint8)ELyraAbilityActivationGroup::MAX];
};
