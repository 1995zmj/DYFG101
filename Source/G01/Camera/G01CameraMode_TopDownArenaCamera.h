

#pragma once

#include "G01CameraMode.h"
#include "Curves/CurveFloat.h"
#include "G01CameraMode_TopDownArenaCamera.generated.h"

class UObject;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class UG01CameraMode_TopDownArenaCamera : public UG01CameraMode
{
	GENERATED_BODY()

public:

	UG01CameraMode_TopDownArenaCamera();

protected:

	//~ULyraCameraMode interface
	virtual void UpdateView(float DeltaTime) override;
	//~End of ULyraCameraMode interface

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	float ArenaWidth;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	float ArenaHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	FRotator DefaultPivotRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	FRuntimeFloatCurve BoundsSizeToDistance;
};