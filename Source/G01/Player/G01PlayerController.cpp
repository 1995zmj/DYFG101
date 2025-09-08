// Fill out your copyright notice in the Description page of Project Settings.


#include "G01PlayerController.h"
#include "Camera/G01PlayerCameraManager.h"
#include "G01PlayerState.h"
#include "AbilitySystem/G01AbilitySystemComponent.h"
#include "UI/G01HUD.h"

AG01PlayerController::AG01PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = AG01PlayerCameraManager::StaticClass();

}

void AG01PlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AG01PlayerController::BeginPlay()
{
	Super::BeginPlay();
#if WITH_RPC_REGISTRY
	FHttpServerModule::Get().StartAllListeners();
	int32 RpcPort = 0;
	if (FParse::Value(FCommandLine::Get(), TEXT("rpcport="), RpcPort))
	{
		ULyraGameplayRpcRegistrationComponent* ObjectInstance = ULyraGameplayRpcRegistrationComponent::GetInstance();
		if (ObjectInstance && ObjectInstance->IsValidLowLevel())
		{
			ObjectInstance->RegisterAlwaysOnHttpCallbacks();
			ObjectInstance->RegisterInMatchHttpCallbacks();
		}
	}
#endif
	SetActorHiddenInGame(false);
}

void AG01PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AG01PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

AG01PlayerState* AG01PlayerController::GetG01PlayerState() const
{
	return CastChecked<AG01PlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UG01AbilitySystemComponent* AG01PlayerController::GetG01AbilitySystemComponent() const
{
	const AG01PlayerState* PS = GetG01PlayerState();
	return (PS ? PS->GetG01AbilitySystemComponent() : nullptr);
}

AG01HUD* AG01PlayerController::GetG01HUD() const
{
	return CastChecked<AG01HUD>(GetHUD(), ECastCheckedType::NullAllowed);
}


void AG01PlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UG01AbilitySystemComponent* ASC = GetG01AbilitySystemComponent())
	{
		ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

void AG01PlayerController::SetIsAutoRunning(const bool bEnabled)
{
	/*const bool bIsAutoRunning = GetIsAutoRunning();
	if (bEnabled != bIsAutoRunning)
	{
		if (!bEnabled)
		{
			OnEndAutoRun();
		}
		else
		{
			OnStartAutoRun();
		}
	}*/
}

void AG01PlayerController::OnCameraPenetratingTarget()
{
	bHideViewTargetPawnNextFrame = true;
}
