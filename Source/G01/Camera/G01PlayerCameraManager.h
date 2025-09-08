// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "G01PlayerCameraManager.generated.h"

class FDebugDisplayInfo;
class UCanvas;
class UObject;

#define G01_CAMERA_DEFAULT_FOV			(80.0f)
#define G01_CAMERA_DEFAULT_PITCH_MIN	(-89.0f)
#define G01_CAMERA_DEFAULT_PITCH_MAX	(89.0f)

class UG01UICameraManagerComponent;

/**
 * ALyraPlayerCameraManager
 *
 *	The base player camera manager class used by this project.
 */
UCLASS(notplaceable, MinimalAPI)
class AG01PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:

	AG01PlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	UG01UICameraManagerComponent* GetUICameraComponent() const;

protected:

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;

private:
	/** The UI Camera Component, controls the camera when UI is doing something important that gameplay doesn't get priority over. */
	UPROPERTY(Transient)
	TObjectPtr<UG01UICameraManagerComponent> UICamera;
};
