

#pragma once

#include "AbilitySystemGlobals.h"

#include "G01AbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class UG01AbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	//~UAbilitySystemGlobals interface
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	//~End of UAbilitySystemGlobals interface
};
