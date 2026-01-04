// Fill out your copyright notice in the Description page of Project Settings.


#include "G01LocalPlayer.h"
#include "Settings/G01SettingsShared.h"
#include "Settings/G01SettingsLocal.h"

UG01SettingsLocal* UG01LocalPlayer::GetLocalSettings() const
{
	return UG01SettingsLocal::Get();
}

UG01SettingsShared* UG01LocalPlayer::GetSharedSettings() const
{
	if (!SharedSettings)
	{
		// On PC it's okay to use the sync load because it only checks the disk
		// This could use a platform tag to check for proper save support instead
		bool bCanLoadBeforeLogin = PLATFORM_DESKTOP;

		if (bCanLoadBeforeLogin)
		{
			SharedSettings = UG01SettingsShared::LoadOrCreateSettings(this);
		}
		else
		{
			// We need to wait for user login to get the real settings so return temp ones
			SharedSettings = UG01SettingsShared::CreateTemporarySettings(this);
		}
	}

	return SharedSettings;
}
