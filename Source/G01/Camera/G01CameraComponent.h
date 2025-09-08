// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "G01CameraComponent.generated.h"

class UG01CameraMode;
class UG01CameraModeStack;
struct FGameplayTag;

DECLARE_DELEGATE_RetVal(TSubclassOf<UG01CameraMode>, FG01CameraModeDelegate);
/**
 * 
 */
UCLASS()
class G01_API UG01CameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	UG01CameraComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the camera component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "Lyra|Camera")
	static UG01CameraComponent* FindCameraComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UG01CameraComponent>() : nullptr); }

	// Returns the target actor that the camera is looking at.
	virtual AActor* GetTargetActor() const { return GetOwner(); }

	// Delegate used to query for the best camera mode.
	FG01CameraModeDelegate DetermineCameraModeDelegate;


	// Add an offset to the field of view.The offset is only for one frame, it gets cleared once it is applied.
	void AddFieldOfViewOffset(float FovOffset) { FieldOfViewOffset += FovOffset; }

	virtual void DrawDebug(UCanvas * Canvas) const;

	// Gets the tag associated with the top layer and the blend weight of it
	void GetBlendInfo(float& OutWeightOfTopLayer, FGameplayTag & OutTagOfTopLayer) const;

protected:

	virtual void OnRegister() override;
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	virtual void UpdateCameraModes();

protected:
	// Stack used to blend the camera modes.
	UPROPERTY()
	TObjectPtr<UG01CameraModeStack> CameraModeStack;

	// Offset applied to the field of view.The offset is only for one frame, it gets cleared once it is applied.
	float FieldOfViewOffset;
};
