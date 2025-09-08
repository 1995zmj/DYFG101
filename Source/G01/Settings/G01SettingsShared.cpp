
#include "G01SettingsShared.h"
#include "Player/G01LocalPlayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01SettingsShared)

static FString SHARED_SETTINGS_SLOT_NAME = TEXT("SharedGameSettings");


UG01SettingsShared* UG01SettingsShared::CreateTemporarySettings(const UG01LocalPlayer* LocalPlayer)
{
	// This is not loaded from disk but should be set up to save
	UG01SettingsShared* SharedSettings = Cast<UG01SettingsShared>(CreateNewSaveGameForLocalPlayer(UG01SettingsShared::StaticClass(), LocalPlayer, SHARED_SETTINGS_SLOT_NAME));

	SharedSettings->ApplySettings();

	return SharedSettings;
}

UG01SettingsShared* UG01SettingsShared::LoadOrCreateSettings(const UG01LocalPlayer* LocalPlayer)
{
	// This will stall the main thread while it loads
	UG01SettingsShared* SharedSettings = Cast<UG01SettingsShared>(LoadOrCreateSaveGameForLocalPlayer(UG01SettingsShared::StaticClass(), LocalPlayer, SHARED_SETTINGS_SLOT_NAME));

	SharedSettings->ApplySettings();

	return SharedSettings;
}

void UG01SettingsShared::ApplySettings()
{
}
