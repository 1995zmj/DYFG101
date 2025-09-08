// Fill out your copyright notice in the Description page of Project Settings.


#include "G01GameInstance.h"
#include "Components/GameFrameworkComponentManager.h"
#include "G01GameplayTags.h"

void UG01GameInstance::Init()
{
	Super::Init();

	// Register our custom init states
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);

	if (ensure(ComponentManager))
	{
		ComponentManager->RegisterInitState(G01GameplayTags::InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(G01GameplayTags::InitState_DataAvailable, false, G01GameplayTags::InitState_Spawned);
		ComponentManager->RegisterInitState(G01GameplayTags::InitState_DataInitialized, false, G01GameplayTags::InitState_DataAvailable);
		ComponentManager->RegisterInitState(G01GameplayTags::InitState_GameplayReady, false, G01GameplayTags::InitState_DataInitialized);
	}
}
