


#include "G01CameraMode_TopDownArenaCamera.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(G01CameraMode_TopDownArenaCamera)

UG01CameraMode_TopDownArenaCamera::UG01CameraMode_TopDownArenaCamera()
{
	ArenaWidth = 1000.0f;
	ArenaHeight = 1000.0f;
}

void UG01CameraMode_TopDownArenaCamera::UpdateView(float DeltaTime)
{
	FBox ArenaBounds(FVector(-ArenaWidth, -ArenaHeight, 0.0f), FVector(ArenaWidth, ArenaHeight, 100.0f));

	const double BoundsMaxComponent = ArenaBounds.GetSize().GetMax();

	const double CameraLoftDistance = BoundsSizeToDistance.GetRichCurveConst()->Eval(BoundsMaxComponent);

	FVector PivotLocation = ArenaBounds.GetCenter() - DefaultPivotRotation.Vector() * CameraLoftDistance;

	FRotator PivotRotation = DefaultPivotRotation;

	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;
}

