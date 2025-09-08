

#pragma once

#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayAbilitySpecHandle.h"
#include "Logging/LogMacros.h"

#include "G01GamePhaseSubsystem.generated.h"

class UG01GamePhaseAbility;

DECLARE_LOG_CATEGORY_EXTERN(LogG01GamePhase, Log, All);

DECLARE_DYNAMIC_DELEGATE_OneParam(FG01GamePhaseDynamicDelegate, const UG01GamePhaseAbility*, Phase);
DECLARE_DELEGATE_OneParam(FG01GamePhaseDelegate, const UG01GamePhaseAbility* Phase);

DECLARE_DYNAMIC_DELEGATE_OneParam(FG01GamePhaseTagDynamicDelegate, const FGameplayTag&, PhaseTag);
DECLARE_DELEGATE_OneParam(FG01GamePhaseTagDelegate, const FGameplayTag& PhaseTag);

UENUM(BlueprintType)
enum class EPhaseTagMatchType : uint8
{
	// An exact match will only receive messages with exactly the same channel
	// (e.g., registering for "A.B" will match a broadcast of A.B but not A.B.C)
	ExactMatch,

	// A partial match will receive any messages rooted in the same channel
	// (e.g., registering for "A.B" will match a broadcast of A.B as well as A.B.C)
	PartialMatch
};


/**
 * 
 */
UCLASS()
class UG01GamePhaseSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UG01GamePhaseSubsystem();


	virtual void PostInitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void StartPhase(TSubclassOf<UG01GamePhaseAbility> PhaseAbility, FG01GamePhaseDelegate PhaseEndedCallback = FG01GamePhaseDelegate());

protected:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Game Phase", meta = (DisplayName = "Start Phase", AutoCreateRefTerm = "PhaseEnded"))
	void K2_StartPhase(TSubclassOf<UG01GamePhaseAbility> Phase, const FG01GamePhaseDynamicDelegate& PhaseEnded);

	void OnBeginPhase(const UG01GamePhaseAbility* PhaseAbility, const FGameplayAbilitySpecHandle PhaseAbilityHandle);
	void OnEndPhase(const UG01GamePhaseAbility* PhaseAbility, const FGameplayAbilitySpecHandle PhaseAbilityHandle);

private:
	struct FG01GamePhaseEntry
	{
	public:
		FGameplayTag PhaseTag;
		FG01GamePhaseDelegate PhaseEndedCallback;
	};

	TMap<FGameplayAbilitySpecHandle, FG01GamePhaseEntry> ActivePhaseMap;

	struct FPhaseObserver
	{
	public:
		bool IsMatch(const FGameplayTag& ComparePhaseTag) const;

		FGameplayTag PhaseTag;
		EPhaseTagMatchType MatchType = EPhaseTagMatchType::ExactMatch;
		FG01GamePhaseTagDelegate PhaseCallback;
	};

	TArray<FPhaseObserver> PhaseStartObservers;
	TArray<FPhaseObserver> PhaseEndObservers;

	friend class UG01GamePhaseAbility;
};

