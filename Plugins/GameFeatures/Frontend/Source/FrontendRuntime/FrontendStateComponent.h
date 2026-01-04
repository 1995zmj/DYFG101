

#pragma once

#include "Components/GameStateComponent.h"
#include "ControlFlowNode.h"

#include "FrontendStateComponent.generated.h"

class UG01ExperienceDefinition;
class UCommonActivatableWidget;

UCLASS(Abstract)
class UFrontendStateComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFrontendStateComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

	//~ILoadingProcessInterface interface
	//virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;
	//~End of ILoadingProcessInterface

private:
	void OnExperienceLoaded(const UG01ExperienceDefinition* Experience);

	void FlowStep_WaitForUserInitialization(FControlFlowNodeRef SubFlow);
	void FlowStep_TryShowPressStartScreen(FControlFlowNodeRef SubFlow);
	void FlowStep_TryJoinRequestedSession(FControlFlowNodeRef SubFlow);
	void FlowStep_TryShowMainScreen(FControlFlowNodeRef SubFlow);

	bool bShouldShowLoadingScreen = true;

	UPROPERTY(EditAnywhere, Category = UI)
	TSoftClassPtr<UCommonActivatableWidget> PressStartScreenClass;

	UPROPERTY(EditAnywhere, Category = UI)
	TSoftClassPtr<UCommonActivatableWidget> MainScreenClass;

	TSharedPtr<FControlFlow> FrontEndFlow;

	// If set, this is the in-progress press start screen task
	FControlFlowNodePtr InProgressPressStartScreen;

	FDelegateHandle OnJoinSessionCompleteEventHandle;

};
