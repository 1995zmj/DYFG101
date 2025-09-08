// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLocalPlayer.h"
#include "G01LocalPlayer.generated.h"

class UG01SettingsShared;

/**
 * 
 */
UCLASS()
class UG01LocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:
	UFUNCTION()
	UG01SettingsShared* GetSharedSettings() const;

private:
	UPROPERTY(Transient)
	mutable TObjectPtr<UG01SettingsShared> SharedSettings;
};
