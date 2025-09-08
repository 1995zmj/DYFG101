#include "G01AbilitySystemGlobals.h"
#include "G01GameplayEffectContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01AbilitySystemGlobals)


FGameplayEffectContext* UG01AbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FG01GameplayEffectContext();
}

