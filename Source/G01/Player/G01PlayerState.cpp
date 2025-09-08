// Fill out your copyright notice in the Description page of Project Settings.


#include "G01PlayerState.h"
#include "G01LogChannels.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"
#include "Character/G01PawnData.h"
#include "GameModes/G01ExperienceManagerComponent.h"
#include "GameModes/G01GameMode.h"
#include "AbilitySystem/G01AbilitySystemComponent.h"
#include "G01PlayerController.h"
#include "AbilitySystem/G01AbilitySet.h"
#include "Components/GameFrameworkComponentManager.h"



#include UE_INLINE_GENERATED_CPP_BY_NAME(G01PlayerState)


const FName AG01PlayerState::NAME_G01AbilityReady("G01AbilitiesReady");

AG01PlayerState::AG01PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	//, MyPlayerConnectionType(ELyraPlayerConnectionType::Player)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UG01AbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);
	//AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// These attribute sets will be detected by AbilitySystemComponent::InitializeComponent. Keeping a reference so that the sets don't get garbage collected before that.
	//HealthSet = CreateDefaultSubobject<ULyraHealthSet>(TEXT("HealthSet"));
	//CombatSet = CreateDefaultSubobject<ULyraCombatSet>(TEXT("CombatSet"));

	// AbilitySystemComponent needs to be updated at a high frequency.
	//SetNetUpdateFrequency(100.0f);

	/*MyTeamID = FGenericTeamId::NoTeam;
	MySquadID = INDEX_NONE;*/
}


AG01PlayerController* AG01PlayerState::GetG01PlayerController() const
{
	return Cast<AG01PlayerController>(GetOwner());
}

UAbilitySystemComponent* AG01PlayerState::GetAbilitySystemComponent() const
{
	return GetG01AbilitySystemComponent();
}

void AG01PlayerState::SetPawnData(const UG01PawnData* InPawnData)
{
	check(InPawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		UE_LOG(LogG01, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}

	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, PawnData, this);
	PawnData = InPawnData;

	for (const UG01AbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, NAME_G01AbilityReady);

	ForceNetUpdate();
}

void AG01PlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AG01PlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());

	UWorld* World = GetWorld();
	if (World && World->IsGameWorld() && World->GetNetMode() != NM_Client)
	{
		AGameStateBase* GameState = GetWorld()->GetGameState();
		check(GameState);
		UG01ExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UG01ExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	}
}

void AG01PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PawnData, SharedParams);
	/*DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MyPlayerConnectionType, SharedParams)
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MyTeamID, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MySquadID, SharedParams);

	SharedParams.Condition = ELifetimeCondition::COND_SkipOwner;
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, ReplicatedViewRotation, SharedParams);

	DOREPLIFETIME(ThisClass, StatTags);*/
}

void AG01PlayerState::OnExperienceLoaded(const UG01ExperienceDefinition* CurrentExperience)
{
	AG01GameMode* GameMode = GetWorld()->GetAuthGameMode<AG01GameMode>();
	if (const UG01PawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController()))
	{
		SetPawnData(NewPawnData);
	}
	else
	{
		UE_LOG(LogG01, Error, TEXT("ALyraPlayerState::OnExperienceLoaded(): Unable to find PawnData to initialize player state [%s]!"), *GetNameSafe(this));
	}
}

void AG01PlayerState::OnRep_PawnData()
{
}
