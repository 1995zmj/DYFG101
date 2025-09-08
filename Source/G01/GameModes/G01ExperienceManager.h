// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/EngineSubsystem.h"
#include "G01ExperienceManager.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UG01ExperienceManager : public UEngineSubsystem
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	void OnPlayInEditorBegun();

	static void NotifyOfPluginActivation(const FString PluginURL);
	static bool RequestToDeactivatePlugin(const FString PluginURL);
#else
	inline void UG01ExperienceManager::OnPlayInEditorBegun()
	{
	}
	static void NotifyOfPluginActivation(const FString PluginURL) {}
	static bool RequestToDeactivatePlugin(const FString PluginURL) { return true; }
#endif

private:
	// The map of requests to active count for a given game feature plugin
	// (to allow first in, last out activation management during PIE)
	TMap<FString, int32> GameFeaturePluginRequestCountMap;
};
