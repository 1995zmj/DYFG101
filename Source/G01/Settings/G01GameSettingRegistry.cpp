// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/G01GameSettingRegistry.h"
#include "Player/G01LocalPlayer.h"
#include "GameSettingCollection.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01GameSettingRegistry)

UG01GameSettingRegistry::UG01GameSettingRegistry()
{
}

UG01GameSettingRegistry* UG01GameSettingRegistry::Get(UG01LocalPlayer* InLocalPlayer)
{
	UG01GameSettingRegistry* Registry = FindObject<UG01GameSettingRegistry>(InLocalPlayer, TEXT("G01GameSettingRegistry"), true);
	if (Registry == nullptr)
	{
		Registry = NewObject<UG01GameSettingRegistry>(InLocalPlayer, TEXT("G01GameSettingRegistry"));
		Registry->Initialize(InLocalPlayer);
	}

	return Registry;
}

bool UG01GameSettingRegistry::IsFinishedInitializing() const
{
	if (Super::IsFinishedInitializing())
	{
		if (UG01LocalPlayer* LocalPlayer = Cast<UG01LocalPlayer>(OwningLocalPlayer))
		{
			if (LocalPlayer->GetSharedSettings() == nullptr)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

void UG01GameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	UG01LocalPlayer* LocalPlayer = Cast<UG01LocalPlayer>(InLocalPlayer);

	/*VideoSettings = InitializeVideoSettings(LocalPlayer);
	InitializeVideoSettings_FrameRates(VideoSettings, LocalPlayer);
	RegisterSetting(VideoSettings);*/

	AudioSettings = InitializeAudioSettings(LocalPlayer);
	RegisterSetting(AudioSettings);

	GameplaySettings = InitializeGameplaySettings(LocalPlayer);
	RegisterSetting(GameplaySettings);

	/*MouseAndKeyboardSettings = InitializeMouseAndKeyboardSettings(LocalPlayer);
	RegisterSetting(MouseAndKeyboardSettings);

	GamepadSettings = InitializeGamepadSettings(LocalPlayer);
	RegisterSetting(GamepadSettings);*/
}

void UG01GameSettingRegistry::SaveChanges()
{
	Super::SaveChanges();

	//if (UG01LocalPlayer* LocalPlayer = Cast<UG01LocalPlayer>(OwningLocalPlayer))
	//{
	//	// Game user settings need to be applied to handle things like resolution, this saves indirectly
	//	LocalPlayer->GetLocalSettings()->ApplySettings(false);

	//	LocalPlayer->GetSharedSettings()->ApplySettings();
	//	LocalPlayer->GetSharedSettings()->SaveSettings();
	//}
}
