// Fill out your copyright notice in the Description page of Project Settings.


#include "G01GameState.h"
#include "G01ExperienceManagerComponent.h"
#include "AbilitySystem/G01AbilitySystemComponent.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(G01GameState)

AG01GameState::AG01GameState(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UG01AbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	/*AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);*/


	ExperienceManagerComponent = CreateDefaultSubobject<UG01ExperienceManagerComponent>((TEXT("ExperienceManagerComponent")));
}

void AG01GameState::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(/*Owner=*/ this, /*Avatar=*/ this);
}

void AG01GameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

UAbilitySystemComponent* AG01GameState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
