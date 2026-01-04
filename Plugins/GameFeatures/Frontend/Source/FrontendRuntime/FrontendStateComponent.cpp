


#include "FrontendStateComponent.h"
#include "GameModes/G01ExperienceManagerComponent.h"
#include "ControlFlowManager.h"
#include "PrimaryGameLayout.h"
#include "NativeGameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FrontendStateComponent)


namespace FrontendTags
{
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_PLATFORM_TRAIT_SINGLEONLINEUSER, "Platform.Trait.SingleOnlineUser");
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");
}

UFrontendStateComponent::UFrontendStateComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UFrontendStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for the experience load to complete
	AGameStateBase* GameState = GetGameStateChecked<AGameStateBase>();
	UG01ExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UG01ExperienceManagerComponent>();
	check(ExperienceComponent);

	// This delegate is on a component with the same lifetime as this one, so no need to unhook it in 
	ExperienceComponent->CallOrRegister_OnExperienceLoaded_HighPriority(FOnExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void UFrontendStateComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

//bool UFrontendStateComponent::ShouldShowLoadingScreen(FString& OutReason) const
//{
//	if (bShouldShowLoadingScreen)
//	{
//		OutReason = TEXT("Frontend Flow Pending...");
//
//		if (FrontEndFlow.IsValid())
//		{
//			const TOptional<FString> StepDebugName = FrontEndFlow->GetCurrentStepDebugName();
//			if (StepDebugName.IsSet())
//			{
//				OutReason = StepDebugName.GetValue();
//			}
//		}
//
//		return true;
//	}
//
//	return false;
//}

void UFrontendStateComponent::OnExperienceLoaded(const UG01ExperienceDefinition* Experience)
{
	FControlFlow& Flow = FControlFlowStatics::Create(this, TEXT("FrontendFlow"))
		.QueueStep(TEXT("Wait For User Initialization"), this, &ThisClass::FlowStep_WaitForUserInitialization)
		.QueueStep(TEXT("Try Show Press Start Screen"), this, &ThisClass::FlowStep_TryShowPressStartScreen)
		.QueueStep(TEXT("Try Join Requested Session"), this, &ThisClass::FlowStep_TryJoinRequestedSession)
		.QueueStep(TEXT("Try Show Main Screen"), this, &ThisClass::FlowStep_TryShowMainScreen);

	Flow.ExecuteFlow();

	FrontEndFlow = Flow.AsShared();
}


void UFrontendStateComponent::FlowStep_WaitForUserInitialization(FControlFlowNodeRef SubFlow)
{
	SubFlow->ContinueFlow();
}

void UFrontendStateComponent::FlowStep_TryShowPressStartScreen(FControlFlowNodeRef SubFlow)
{
	SubFlow->ContinueFlow();
}

void UFrontendStateComponent::FlowStep_TryJoinRequestedSession(FControlFlowNodeRef SubFlow)
{
	SubFlow->ContinueFlow();
}

void UFrontendStateComponent::FlowStep_TryShowMainScreen(FControlFlowNodeRef SubFlow)
{
	if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(this))
	{
		constexpr bool bSuspendInputUntilComplete = true;
		RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(FrontendTags::TAG_UI_LAYER_MENU, bSuspendInputUntilComplete, MainScreenClass,
			[this, SubFlow](EAsyncWidgetLayerState State, UCommonActivatableWidget* Screen) {
				switch (State)
				{
				case EAsyncWidgetLayerState::AfterPush:
					bShouldShowLoadingScreen = false;
					SubFlow->ContinueFlow();
					return;
				case EAsyncWidgetLayerState::Canceled:
					bShouldShowLoadingScreen = false;
					SubFlow->ContinueFlow();
					return;
				}
			});
	}
}

