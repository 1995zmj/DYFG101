// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "G01InputModifiers.generated.h"

/**
 * 
 */
UCLASS()
class G01_API UG01InputModifiers : public UInputModifier
{
	GENERATED_BODY()
};


/** Applies an inversion of axis values based on a setting in the Lyra Shared game settings */
UCLASS(NotBlueprintable, MinimalAPI, meta = (DisplayName = "G01 Aim Inversion Setting"))
class UG01InputModifierAimInversion : public UInputModifier
{
	GENERATED_BODY()

protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
};

