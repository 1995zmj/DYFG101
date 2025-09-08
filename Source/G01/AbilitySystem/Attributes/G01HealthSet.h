

#pragma once

#include "CoreMinimal.h"
#include "G01AttributeSet.h"
#include "G01GameplayTags.h"
#include "G01HealthSet.generated.h"


G01_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
G01_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
G01_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageSelfDestruct);
G01_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
G01_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Lyra_Damage_Message);
/**
 * 
 */
UCLASS()
class G01_API UG01HealthSet : public UG01AttributeSet
{
	GENERATED_BODY()
};
