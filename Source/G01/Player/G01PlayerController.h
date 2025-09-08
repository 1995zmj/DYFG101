// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "Camera/G01CameraAssistInterface.h"

#include "G01PlayerController.generated.h"

class AG01PlayerState;
class UG01AbilitySystemComponent;

/**
 * 
 */
UCLASS(MinimalAPI, Config = Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class  AG01PlayerController : public ACommonPlayerController, public IG01CameraAssistInterface
{
	GENERATED_BODY()

public:

	AG01PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerController")
	AG01PlayerState* GetG01PlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerController")
	UG01AbilitySystemComponent* GetG01AbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerController")
	AG01HUD* GetG01HUD() const;


	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//~End of AActor interface

	//~APlayerController interface
	/*virtual void ReceivedPlayer() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetPlayer(UPlayer* InPlayer) override;
	virtual void AddCheats(bool bForce) override;
	virtual void UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId) override;
	virtual void UpdateHiddenComponents(const FVector& ViewLocation, TSet<FPrimitiveComponentId>& OutHiddenComponents) override;
	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;*/
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	//~End of APlayerController interface

	UFUNCTION(BlueprintCallable, Category = "Lyra|Character")
	void SetIsAutoRunning(const bool bEnabled);

	//~ILyraCameraAssistInterface interface
	virtual void OnCameraPenetratingTarget() override;
	//~End of ILyraCameraAssistInterface interface

protected:
	bool bHideViewTargetPawnNextFrame = false;
};
