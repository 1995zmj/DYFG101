// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "G01DeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config=EditorPerProjectUserSettings, MinimalAPI)
class UG01DeveloperSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
public:
	// The experience override to use for Play in Editor (if not set, the default for the world settings of the open map will be used)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, config, Category=Experience, meta=(AllowedTypes="ExperienceDefinition"))
	FPrimaryAssetId ExperienceOverride;
};
