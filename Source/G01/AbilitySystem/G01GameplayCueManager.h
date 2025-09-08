

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "G01GameplayCueManager.generated.h"

/**
 * 
 */
UCLASS()
class UG01GameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()

public:
	UG01GameplayCueManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static UG01GameplayCueManager* Get();


	// Updates the bundles for the singular gameplay cue primary asset
	void RefreshGameplayCuePrimaryAsset();
};
