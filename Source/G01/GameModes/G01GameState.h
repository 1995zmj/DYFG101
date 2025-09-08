// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularGameState.h"
#include "AbilitySystemInterface.h"
#include "G01GameState.generated.h"

#define UE_API G01_API

class UG01ExperienceManagerComponent;
class UG01AbilitySystemComponent;

/**
 * 
 */
UCLASS(MinimalAPI, Config = Game)
class AG01GameState : public AModularGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AG01GameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	//~End of AActor interface


	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of IAbilitySystemInterface

private:
	
	UPROPERTY()
	TObjectPtr<UG01ExperienceManagerComponent> ExperienceManagerComponent;

	// The ability system component subobject for game-wide things (primarily gameplay cues)
	UPROPERTY(VisibleAnywhere, Category = "Lyra|GameState")
	TObjectPtr<UG01AbilitySystemComponent> AbilitySystemComponent;
};

#undef UE_API
