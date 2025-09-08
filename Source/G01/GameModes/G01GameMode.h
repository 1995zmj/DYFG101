// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularGameMode.h"
#include "G01GameMode.generated.h"

#define UE_API G01_API

class UG01ExperienceDefinition;
struct FPrimaryAssetId;
class UG01PawnData;
/**
 * 
 */
UCLASS(MinimalAPI, Config = Game, Meta = (ShortTooltip = "The base game mode class used by this project."))
class AG01GameMode : public AModularGameModeBase
{
	GENERATED_BODY()
public:
	AG01GameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	const UG01PawnData* GetPawnDataForController(const AController* InController) const;
	
	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:
	void OnExperienceLoaded(const UG01ExperienceDefinition* CurrentExperience);
	bool IsExperienceLoaded() const;

	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource);
	void HandleMatchAssignmentIfNotExpectingOne();
};

#undef UE_API
