

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "G01GameplayAbility.generated.h"


UENUM(BlueprintType)
enum class EG01AbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

/**
 * 
 */
UCLASS()
class G01_API UG01GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	EG01AbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
protected:
	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Ability Activation")
	EG01AbilityActivationPolicy ActivationPolicy;

};
