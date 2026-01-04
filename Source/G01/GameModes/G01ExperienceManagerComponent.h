// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"

#include "G01ExperienceManagerComponent.generated.h"

#define UE_API G01_API


class UG01ExperienceDefinition;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnExperienceLoaded, const UG01ExperienceDefinition* /*Experience*/);

namespace UE::GameFeatures { struct FResult; }
//
//DECLARE_MULTICAST_DELEGATE_OneParam(FOnExperienceLoaded, const UExperienceDefinition* /*Experience*/);
//
enum class EExperienceLoadState
{
	Unloaded,
	Loading,
	LoadingGameFeatures,
	LoadingChaosTestingDelay,
	ExecutingActions,
	Loaded,
	Deactivating
};

UCLASS()
class UG01ExperienceManagerComponent final: public UGameStateComponent
{
	GENERATED_BODY()

public:
	UG01ExperienceManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	void SetCurrentExperience(FPrimaryAssetId ExperienceId);

	UE_API void CallOrRegister_OnExperienceLoaded_HighPriority(FOnExperienceLoaded::FDelegate&& Delegate);

	UE_API void CallOrRegister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate&& Delegate);
	
	UE_API void CallOrRegister_OnExperienceLoaded_LowPriority(FOnExperienceLoaded::FDelegate&& Delegate);

	const UG01ExperienceDefinition* GetCurrentExperienceChecked() const;

	bool IsExperienceLoaded() const;
private:
	UFUNCTION()
	void OnRep_CurrentExperience();

	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result);
	void OnExperienceFullLoadCompleted();

	void OnActionDeactivationCompleted();
	void OnAllActionsDeactivated();

private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentExperience)
	TObjectPtr<const UG01ExperienceDefinition> CurrentExperience;

	EExperienceLoadState LoadState = EExperienceLoadState::Unloaded;

	int32 NumGameFeaturePluginsLoading = 0;
	TArray<FString> GameFeaturePluginURLs;

	int32 NumObservedPausers = 0;
	int32 NumExpectedPausers = 0;

	/**
	 * Delegate called when the experience has finished loading just before others
	 * (e.g., subsystems that set up for regular gameplay)
	 */
	FOnExperienceLoaded OnExperienceLoaded_HighPriority;

	/** Delegate called when the experience has finished loading */
	FOnExperienceLoaded OnExperienceLoaded;

	/** Delegate called when the experience has finished loading */
	FOnExperienceLoaded OnExperienceLoaded_LowPriority;
};
#undef UE_API