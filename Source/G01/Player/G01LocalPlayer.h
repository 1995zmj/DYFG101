// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLocalPlayer.h"
#include "G01LocalPlayer.generated.h"

class UG01SettingsShared;
class UG01SettingsLocal;

/**
 * 
 */
UCLASS()
class UG01LocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:
	/** Gets the local settings for this player, this is read from config files at process startup and is always valid */
	UFUNCTION()
	UG01SettingsLocal* GetLocalSettings() const;

	/** Gets the shared setting for this player, this is read using the save game system so may not be correct until after user login */
	UFUNCTION()
	UG01SettingsShared* GetSharedSettings() const;

private:
	UPROPERTY(Transient)
	mutable TObjectPtr<UG01SettingsShared> SharedSettings;
};
