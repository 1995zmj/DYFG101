// Fill out your copyright notice in the Description page of Project Settings.


#include "G01InputModifiers.h"
#include "Settings/G01SettingsShared.h"
#include "Player/G01LocalPlayer.h"
#include "EnhancedPlayerInput.h"


//////////////////////////////////////////////////////////////////////
// LyraInputModifiersHelpers

namespace G01InputModifiersHelpers
{
	/** Returns the owning LyraLocalPlayer of an Enhanced Player Input pointer */
	static UG01LocalPlayer* GetLocalPlayer(const UEnhancedPlayerInput* PlayerInput)
	{
		if (PlayerInput)
		{
			if (APlayerController* PC = Cast<APlayerController>(PlayerInput->GetOuter()))
			{
				return Cast<UG01LocalPlayer>(PC->GetLocalPlayer());
			}
		}
		return nullptr;
	}

}

FInputActionValue UG01InputModifierAimInversion::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	UG01LocalPlayer* LocalPlayer = G01InputModifiersHelpers::GetLocalPlayer(PlayerInput);
	if (!LocalPlayer)
	{
		return CurrentValue;
	}

	UG01SettingsShared* Settings = LocalPlayer->GetSharedSettings();
	ensure(Settings);

	FVector NewValue = CurrentValue.Get<FVector>();

	if (Settings->GetInvertVerticalAxis())
	{
		NewValue.Y *= -1.0f;
	}

	if (Settings->GetInvertHorizontalAxis())
	{
		NewValue.X *= -1.0f;
	}

	return NewValue;
}
