#pragma once

#include "GameFramework/SaveGame.h"
#include "UObject/ObjectPtr.h"
#include "G01SettingsShared.generated.h"

class UObject;
struct FFrame;

UENUM(BlueprintType)
enum class EColorBlindMode : uint8
{
	Off,
	// Deuteranope (green weak/blind)
	Deuteranope,
	// Protanope (red weak/blind)
	Protanope,
	// Tritanope(blue weak / bind)
	Tritanope
};

UENUM(BlueprintType)
enum class ELyraAllowBackgroundAudioSetting : uint8
{
	Off,
	AllSounds,

	Num UMETA(Hidden),
};

UENUM(BlueprintType)
enum class ELyraGamepadSensitivity : uint8
{
	Invalid = 0		UMETA(Hidden),

	Slow			UMETA(DisplayName = "01 - Slow"),
	SlowPlus		UMETA(DisplayName = "02 - Slow+"),
	SlowPlusPlus	UMETA(DisplayName = "03 - Slow++"),
	Normal			UMETA(DisplayName = "04 - Normal"),
	NormalPlus		UMETA(DisplayName = "05 - Normal+"),
	NormalPlusPlus	UMETA(DisplayName = "06 - Normal++"),
	Fast			UMETA(DisplayName = "07 - Fast"),
	FastPlus		UMETA(DisplayName = "08 - Fast+"),
	FastPlusPlus	UMETA(DisplayName = "09 - Fast++"),
	Insane			UMETA(DisplayName = "10 - Insane"),

	MAX				UMETA(Hidden),
};

class UG01LocalPlayer;

/**
 * ULyraSettingsShared - The "Shared" settings are stored as part of the USaveGame system, these settings are not machine
 * specific like the local settings, and are safe to store in the cloud - and 'share' them.  Using the save game system
 * we can also store settings per player, so things like controller keybind preferences should go here, because if those
 * are stored in the local settings all users would get them.
 *
 */
UCLASS()
class UG01SettingsShared : public ULocalPlayerSaveGame
{
	GENERATED_BODY()

public:

	/** Creates a temporary settings object, this will be replaced by one loaded from the user's save game */
	static UG01SettingsShared* CreateTemporarySettings(const UG01LocalPlayer* LocalPlayer);

	/** Synchronously loads a settings object, this is not valid to call before login */
	static UG01SettingsShared* LoadOrCreateSettings(const UG01LocalPlayer* LocalPlayer);

	UFUNCTION()
	bool GetInvertVerticalAxis() const { return bInvertVerticalAxis; }

	UFUNCTION()
	bool GetInvertHorizontalAxis() const { return bInvertHorizontalAxis; }

	/** Applies the current settings to the player */
	void ApplySettings();
private:
	UPROPERTY()
	bool bInvertVerticalAxis = false;

	UPROPERTY()
	bool bInvertHorizontalAxis = false;
};