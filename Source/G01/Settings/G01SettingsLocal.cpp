
#include "G01SettingsLocal.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(G01SettingsLocal)




UG01SettingsLocal::UG01SettingsLocal()
{
	/*if (!HasAnyFlags(RF_ClassDefaultObject) && FSlateApplication::IsInitialized())
	{
		OnApplicationActivationStateChangedHandle = FSlateApplication::Get().OnApplicationActivationStateChanged().AddUObject(this, &ThisClass::OnAppActivationStateChanged);
	}

	bEnableScalabilitySettings = ULyraPlatformSpecificRenderingSettings::Get()->bSupportsGranularVideoQualitySettings;*/

	SetToDefaults();
}


UG01SettingsLocal* UG01SettingsLocal::Get()
{
	return GEngine ? CastChecked<UG01SettingsLocal>(GEngine->GetGameUserSettings()) : nullptr;
}

void UG01SettingsLocal::BeginDestroy()
{
	/*if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().OnApplicationActivationStateChanged().Remove(OnApplicationActivationStateChangedHandle);
	}*/
	Super::BeginDestroy();
}

void UG01SettingsLocal::SetToDefaults()
{
	Super::SetToDefaults();

	/*bUseHeadphoneMode = false;
	bUseHDRAudioMode = false;
	bSoundControlBusMixLoaded = false;
	bEnableLatencyTrackingStats = ULyraSettingsLocal::DoesPlatformSupportLatencyTrackingStats();

	const ULyraPlatformSpecificRenderingSettings* PlatformSettings = ULyraPlatformSpecificRenderingSettings::Get();
	UserChosenDeviceProfileSuffix = PlatformSettings->DefaultDeviceProfileSuffix;
	DesiredUserChosenDeviceProfileSuffix = UserChosenDeviceProfileSuffix;

	FrameRateLimit_InMenu = 144.0f;
	FrameRateLimit_WhenBackgrounded = 30.0f;
	FrameRateLimit_OnBattery = 60.0f;

	MobileFrameRateLimit = GetDefaultMobileFrameRate();
	DesiredMobileFrameRateLimit = MobileFrameRateLimit;*/
}



//////////////////////////////////////////////////////////////////
// Audio - Sound
float UG01SettingsLocal::GetOverallVolume() const
{
	return OverallVolume;
}

void UG01SettingsLocal::SetOverallVolume(float InVolume)
{
	// Cache the incoming volume value
	OverallVolume = InVolume;

	/*
	// Check to see if references to the control buses and control bus mixes have been loaded yet
	// Will likely need to be loaded if this function is the first time a setter has been called from the UI
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}

	// Ensure it's been loaded before continuing
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));

	// Locate the locally cached bus and set the volume on it
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("Music")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, MusicVolume);
		}
	}
	*/
	
}
float UG01SettingsLocal::GetMusicVolume() const
{
	return MusicVolume;
}

void UG01SettingsLocal::SetMusicVolume(float InVolume)
{
	// Cache the incoming volume value
	MusicVolume = InVolume;

	/*
	// Check to see if references to the control buses and control bus mixes have been loaded yet
	// Will likely need to be loaded if this function is the first time a setter has been called from the UI
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}

	// Ensure it's been loaded before continuing
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));

	// Locate the locally cached bus and set the volume on it
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("Music")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, MusicVolume);
		}
	}
	*/
}

float UG01SettingsLocal::GetSoundFXVolume() const
{
	return SoundFXVolume;
}

void UG01SettingsLocal::SetSoundFXVolume(float InVolume)
{
	// Cache the incoming volume value
	SoundFXVolume = InVolume;

	/*
	// Check to see if references to the control buses and control bus mixes have been loaded yet
	// Will likely need to be loaded if this function is the first time a setter has been called from the UI
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}

	// Ensure it's been loaded before continuing
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));

	// Locate the locally cached bus and set the volume on it
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("SoundFX")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, SoundFXVolume);
		}
	}
	*/
}

float UG01SettingsLocal::GetDialogueVolume() const
{
	return DialogueVolume;
}

void UG01SettingsLocal::SetDialogueVolume(float InVolume)
{
	// Cache the incoming volume value
	DialogueVolume = InVolume;


	/*
	// Check to see if references to the control buses and control bus mixes have been loaded yet
	// Will likely need to be loaded if this function is the first time a setter has been called from the UI
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}

	// Ensure it's been loaded before continuing
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));

	// Locate the locally cached bus and set the volume on it
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("Dialogue")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, DialogueVolume);
		}
	}
	*/
}

float UG01SettingsLocal::GetVoiceChatVolume() const
{
	return VoiceChatVolume;
}

void UG01SettingsLocal::SetVoiceChatVolume(float InVolume)
{
	// Cache the incoming volume value
	VoiceChatVolume = InVolume;

	/*
	// Check to see if references to the control buses and control bus mixes have been loaded yet
	// Will likely need to be loaded if this function is the first time a setter has been called from the UI
	if (!bSoundControlBusMixLoaded)
	{
		LoadUserControlBusMix();
	}

	// Ensure it's been loaded before continuing
	ensureMsgf(bSoundControlBusMixLoaded, TEXT("UserControlBusMix Settings Failed to Load."));

	// Locate the locally cached bus and set the volume on it
	if (TObjectPtr<USoundControlBus>* ControlBusDblPtr = ControlBusMap.Find(TEXT("VoiceChat")))
	{
		if (USoundControlBus* ControlBusPtr = *ControlBusDblPtr)
		{
			SetVolumeForControlBus(ControlBusPtr, VoiceChatVolume);
		}
	}
	*/


}

//////////////////////////////////////////////////////////////////
// Audio - Sound
void UG01SettingsLocal::SetAudioOutputDeviceId(const FString& InAudioOutputDeviceId)
{
	AudioOutputDeviceId = InAudioOutputDeviceId;
	OnAudioOutputDeviceChanged.Broadcast(InAudioOutputDeviceId);
}
