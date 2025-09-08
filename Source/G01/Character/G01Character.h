// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "G01Character.generated.h"

class UG01PawnExtensionComponent;
class UG01CameraComponent;

UCLASS(MinimalAPI, Config = Game, Meta = (ShortTooltip = "The base character pawn class used by this project."))
class AG01Character : public AModularCharacter
{
	GENERATED_BODY()

public:
	AG01Character(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleCrouch();
protected:
	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "G01|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UG01PawnExtensionComponent> PawnExtComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "G01|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UG01CameraComponent> CameraComponent;
};
