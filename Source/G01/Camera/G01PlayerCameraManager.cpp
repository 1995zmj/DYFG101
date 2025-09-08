// Fill out your copyright notice in the Description page of Project Settings.


#include "G01PlayerCameraManager.h"
#include "G01UICameraManagerComponent.h"
#include "Engine/Canvas.h"
#include "G01CameraComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01PlayerCameraManager)

class FDebugDisplayInfo;

static FName UICameraComponentName(TEXT("UICamera"));

AG01PlayerCameraManager::AG01PlayerCameraManager(const FObjectInitializer& ObjectInitializer)
{

	DefaultFOV = G01_CAMERA_DEFAULT_FOV;
	ViewPitchMin = G01_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = G01_CAMERA_DEFAULT_PITCH_MAX;

	UICamera = CreateDefaultSubobject<UG01UICameraManagerComponent>(UICameraComponentName);
}

UG01UICameraManagerComponent* AG01PlayerCameraManager::GetUICameraComponent() const
{
	return UICamera;
}

void AG01PlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	/*if (UICamera->NeedsToUpdateViewTarget())
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
		UICamera->UpdateViewTarget(OutVT, DeltaTime);
		return;
	}*/

	Super::UpdateViewTarget(OutVT, DeltaTime);
}

void AG01PlayerCameraManager::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	check(Canvas);

	FDisplayDebugManager& DisplayDebugManager = Canvas->DisplayDebugManager;

	DisplayDebugManager.SetFont(GEngine->GetSmallFont());
	DisplayDebugManager.SetDrawColor(FColor::Yellow);
	DisplayDebugManager.DrawString(FString::Printf(TEXT("LyraPlayerCameraManager: %s"), *GetNameSafe(this)));

	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);

	const APawn* Pawn = (PCOwner ? PCOwner->GetPawn() : nullptr);

	if (const UG01CameraComponent* CameraComponent = UG01CameraComponent::FindCameraComponent(Pawn))
	{
		CameraComponent->DrawDebug(Canvas);
	}
}
