
#include "G01SettingsShared.h"
#include "Player/G01LocalPlayer.h"
#include "Internationalization/Culture.h"

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

//////////////////////////////////////////////////////////////////////
// Shared audio settings
void UG01SettingsShared::SetAllowAudioInBackgroundSetting(EG01AllowBackgroundAudioSetting NewValue)
{
	if (ChangeValueAndDirty(AllowAudioInBackground, NewValue))
	{
		ApplyBackgroundAudioSettings();
	}
}

void UG01SettingsShared::ApplyBackgroundAudioSettings()
{
	if (OwningPlayer && OwningPlayer->IsPrimaryPlayer())
	{
		FApp::SetUnfocusedVolumeMultiplier((AllowAudioInBackground != EG01AllowBackgroundAudioSetting::Off) ? 1.0f : 0.0f);
	}
}

//////////////////////////////////////////////////////////////////////
//Culture / language
void UG01SettingsShared::ApplyCultureSettings()
{
	if (bResetToDefaultCulture)
	{
		const FCulturePtr SystemDefaultCulture = FInternationalization::Get().GetDefaultCulture();
		check(SystemDefaultCulture.IsValid());

		const FString CultureToApply = SystemDefaultCulture->GetName();
		if (FInternationalization::Get().SetCurrentCulture(CultureToApply))
		{
			// Clear this string
			GConfig->RemoveKey(TEXT("Internationalization"), TEXT("Culture"), GGameUserSettingsIni);
			GConfig->Flush(false, GGameUserSettingsIni);
		}
		bResetToDefaultCulture = false;
	}
	else if (!PendingCulture.IsEmpty())
	{
		// SetCurrentCulture may trigger PendingCulture to be cleared (if a culture change is broadcast) so we take a copy of it to work with
		const FString CultureToApply = PendingCulture;
		if (FInternationalization::Get().SetCurrentCulture(CultureToApply))
		{
			// Note: This is intentionally saved to the users config
			// We need to localize text before the player logs in and very early in the loading screen
			GConfig->SetString(TEXT("Internationalization"), TEXT("Culture"), *CultureToApply, GGameUserSettingsIni);
			GConfig->Flush(false, GGameUserSettingsIni);
		}
		ClearPendingCulture();
	}
}

void UG01SettingsShared::ResetCultureToCurrentSettings()
{
	ClearPendingCulture();
	bResetToDefaultCulture = false;
}

const FString& UG01SettingsShared::GetPendingCulture() const
{
	return PendingCulture;
}

void UG01SettingsShared::SetPendingCulture(const FString& NewCulture)
{
	PendingCulture = NewCulture;
	bResetToDefaultCulture = false;
	bIsDirty = true;
}

void UG01SettingsShared::OnCultureChanged()
{
	ClearPendingCulture();
	bResetToDefaultCulture = false;
}

void UG01SettingsShared::ClearPendingCulture()
{
	PendingCulture.Reset();
}

bool UG01SettingsShared::IsUsingDefaultCulture() const
{
	FString Culture;
	GConfig->GetString(TEXT("Internationalization"), TEXT("Culture"), Culture, GGameUserSettingsIni);

	return Culture.IsEmpty();
}

void UG01SettingsShared::ResetToDefaultCulture()
{
	ClearPendingCulture();
	bResetToDefaultCulture = true;
	bIsDirty = true;
}
