// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModularPlayerState.h"
#include "AbilitySystemInterface.h"

#include "G01PlayerState.generated.h"

class UG01PawnData;
class UG01ExperienceDefinition;
/**
 * 
 */
UCLASS(MinimalAPI, Config = Game)
class AG01PlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AG01PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerState")
	AG01PlayerController* GetG01PlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerState")
	UG01AbilitySystemComponent* GetG01AbilitySystemComponent() const { return AbilitySystemComponent; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	void SetPawnData(const UG01PawnData* InPawnData);

	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

	static const FName NAME_G01AbilityReady;

private:
	void OnExperienceLoaded(const UG01ExperienceDefinition* CurrentExperience);

protected:
	UFUNCTION()
	void OnRep_PawnData();
protected:

	UPROPERTY(ReplicatedUsing = OnRep_PawnData)
	TObjectPtr<const UG01PawnData> PawnData;
private:

	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "Lyra|PlayerState")
	TObjectPtr<UG01AbilitySystemComponent> AbilitySystemComponent;
};
