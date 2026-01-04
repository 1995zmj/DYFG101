// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSettingRegistry.h"
#include "DataSource/GameSettingDataSourceDynamic.h" // IWYU pragma: keep

#include "G01GameSettingRegistry.generated.h"


class UG01LocalPlayer;

#define GET_SHARED_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
	MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
		GET_FUNCTION_NAME_STRING_CHECKED(UG01LocalPlayer, GetSharedSettings),				\
		GET_FUNCTION_NAME_STRING_CHECKED(UG01SettingsShared, FunctionOrPropertyName)		\
	}))

#define GET_LOCAL_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
	MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
		GET_FUNCTION_NAME_STRING_CHECKED(UG01LocalPlayer, GetLocalSettings),				\
		GET_FUNCTION_NAME_STRING_CHECKED(UG01SettingsLocal, FunctionOrPropertyName)		\
	}))


UCLASS()
class UG01GameSettingRegistry : public UGameSettingRegistry
{
	GENERATED_BODY()

public:
	UG01GameSettingRegistry();

	static UG01GameSettingRegistry* Get(UG01LocalPlayer* InLocalPlayer);

	virtual void SaveChanges() override;

protected:
	virtual void OnInitialize(ULocalPlayer* InLocalPlayer) override;
	virtual bool IsFinishedInitializing() const override;

	UGameSettingCollection* InitializeVideoSettings(UG01LocalPlayer* InLocalPlayer);
	void InitializeVideoSettings_FrameRates(UGameSettingCollection* Screen, UG01LocalPlayer* InLocalPlayer);
	void AddPerformanceStatPage(UGameSettingCollection* Screen, UG01LocalPlayer* InLocalPlayer);

	UGameSettingCollection* InitializeAudioSettings(UG01LocalPlayer* InLocalPlayer);
	UGameSettingCollection* InitializeGameplaySettings(UG01LocalPlayer* InLocalPlayer);

	UGameSettingCollection* InitializeMouseAndKeyboardSettings(UG01LocalPlayer* InLocalPlayer);
	UGameSettingCollection* InitializeGamepadSettings(UG01LocalPlayer* InLocalPlayer);

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> VideoSettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> AudioSettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> GameplaySettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> MouseAndKeyboardSettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> GamepadSettings;
};
