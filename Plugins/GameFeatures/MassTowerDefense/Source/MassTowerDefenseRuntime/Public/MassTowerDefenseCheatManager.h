

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MassTowerDefenseCheatManager.generated.h"

/**
 *
 */
UCLASS()
class UMassTowerDefenseCheatManager : public UCheatManagerExtension
{
	GENERATED_BODY()

public:
	UFUNCTION(exec, BlueprintCallable)
	void TestString();
};

