// Fill out your copyright notice in the Description page of Project Settings.


#include "G01HeroComponent.h"
#include "EnhancedInputSubsystems.h"
#include "G01GameplayTags.h"
#include "Player/G01PlayerState.h"
#include "Player/G01PlayerController.h"
#include "G01PawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Player/G01LocalPlayer.h"
#include "Character/G01PawnData.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Input/G01InputComponent.h"
#include "G01Character.h"
#include "G01LogChannels.h"
#include "Camera/G01CameraComponent.h"
#include "Camera/G01CameraMode.h"
#include "AbilitySystem/G01AbilitySystemComponent.h"

#if WITH_EDITOR
#include "Misc/UObjectToken.h"
#endif	// WITH_EDITOR

namespace G01Hero
{
	static const float LookYawRate = 300.0f;
	static const float LookPitchRate = 165.0f;
};

const FName UG01HeroComponent::NAME_BindInputsNow("BindInputsNow");
const FName UG01HeroComponent::NAME_ActorFeatureName("Hero");

UG01HeroComponent::UG01HeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//AbilityCameraMode = nullptr;
	bReadyToBindInputs = false;
}

void UG01HeroComponent::AddAdditionalInputConfig(const UG01InputConfig* InputConfig)
{
	TArray<uint32> BindHandles;

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	if (const UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		UG01InputComponent* IC = Pawn->FindComponentByClass<UG01InputComponent>();
		if (ensureMsgf(IC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to ULyraInputComponent or a subclass of it.")))
		{
			IC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);
		}
	}
}

void UG01HeroComponent::RemoveAdditionalInputConfig(const UG01InputConfig* InputConfig)
{
	
}

bool UG01HeroComponent::IsReadyToBindInputs() const
{
	return bReadyToBindInputs;
}

bool UG01HeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	if (!CurrentState.IsValid() && DesiredState ==G01GameplayTags::InitState_Spawned)
	{
		// As long as we have a real pawn, let us transition
		if (Pawn)
		{
			return true;
		}
	}
	else if (CurrentState == G01GameplayTags::InitState_Spawned && DesiredState == G01GameplayTags::InitState_DataAvailable)
	{
		// The player state is required.
		if (!GetPlayerState<AG01PlayerState>())
		{
			return false;
		}

		// If we're authority or autonomous, we need to wait for a controller with registered ownership of the player state.
		if (Pawn->GetLocalRole() != ROLE_SimulatedProxy)
		{
			AController* Controller = GetController<AController>();

			const bool bHasControllerPairedWithPS = (Controller != nullptr) && \
				(Controller->PlayerState != nullptr) && \
				(Controller->PlayerState->GetOwner() == Controller);

			if (!bHasControllerPairedWithPS)
			{
				return false;
			}
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const bool bIsBot = Pawn->IsBotControlled();

		if (bIsLocallyControlled && !bIsBot)
		{
			AG01PlayerController* PC = GetController<AG01PlayerController>();

			// The input component and local player is required when locally controlled.
			if (!Pawn->InputComponent || !PC || !PC->GetLocalPlayer())
			{
				return false;
			}
		}

		return true;
	}
	else if (CurrentState == G01GameplayTags::InitState_DataAvailable && DesiredState == G01GameplayTags::InitState_DataInitialized)
	{
		// Wait for player state and extension component
		AG01PlayerState* PS = GetPlayerState<AG01PlayerState>();

		return PS && Manager->HasFeatureReachedInitState(Pawn, UG01PawnExtensionComponent::NAME_ActorFeatureName, G01GameplayTags::InitState_DataInitialized);
	}
	else if (CurrentState == G01GameplayTags::InitState_DataInitialized && DesiredState == G01GameplayTags::InitState_GameplayReady)
	{
		// TODO add ability initialization checks?
		return true;
	}

	return false;
}

void UG01HeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (CurrentState == G01GameplayTags::InitState_DataAvailable && DesiredState == G01GameplayTags::InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		AG01PlayerState* PS = GetPlayerState<AG01PlayerState>();
		if (!ensure(Pawn && PS))
		{
			return;
		}

		const UG01PawnData* PawnData = nullptr;

		if (UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<UG01PawnData>();

			// The player state holds the persistent data for this player (state that persists across deaths and multiple pawns).
			// The ability system component and attribute sets live on the player state.
			PawnExtComp->InitializeAbilitySystem(PS->GetG01AbilitySystemComponent(), PS);
		}

		if (AG01PlayerController* PC = GetController<AG01PlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}

		// Hook up the delegate for all pawns, in case we spectate later
		if (PawnData)
		{
			if (UG01CameraComponent* CameraComponent = UG01CameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
			}
		}
	}
}

void UG01HeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName == UG01PawnExtensionComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == G01GameplayTags::InitState_DataInitialized)
		{
			// If the extension component says all all other components are initialized, try to progress to next state
			CheckDefaultInitialization();
		}
	}
}

void UG01HeroComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = { G01GameplayTags::InitState_Spawned, G01GameplayTags::InitState_DataAvailable, G01GameplayTags::InitState_DataInitialized, G01GameplayTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

void UG01HeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	// If the player has attempted to move again then cancel auto running
	/*if (AG01PlayerController* PlayerController = Cast<AG01PlayerController>(Controller))
	{
		PlayerController->SetIsAutoRunning(false);
	}*/

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UG01HeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UG01HeroComponent::Input_LookStick(const FInputActionValue& InputActionValue)
{

	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	const UWorld* World = GetWorld();
	check(World);

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X * G01Hero::LookYawRate * World->GetDeltaSeconds());
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y * G01Hero::LookPitchRate * World->GetDeltaSeconds());
	}
}

void UG01HeroComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (AG01Character* Character = GetPawn<AG01Character>())
	{
		Character->ToggleCrouch();
	}
}

void UG01HeroComponent::Input_AutoRun(const FInputActionValue& InputActionValue)
{
	//if (APawn* Pawn = GetPawn<APawn>())
	//{
	//	if (AG01PlayerController* Controller = Cast<AG01PlayerController>(Pawn->GetController()))
	//	{
	//		// Toggle auto running
	//		Controller->SetIsAutoRunning(!Controller->GetIsAutoRunning());
	//	}
	//}
}

TSubclassOf<UG01CameraMode> UG01HeroComponent::DetermineCameraMode() const
{
	if (AbilityCameraMode)
	{
		return AbilityCameraMode;
	}

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return nullptr;
	}

	if (UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UG01PawnData* PawnData = PawnExtComp->GetPawnData<UG01PawnData>())
		{
			return PawnData->DefaultCameraMode;
		}
	}

	return nullptr;
}

void UG01HeroComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetPawn<APawn>())
	{
		UE_LOG(LogG01, Error, TEXT("[ULyraHeroComponent::OnRegister] This component has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint."));

#if WITH_EDITOR
		if (GIsEditor)
		{
			static const FText Message = NSLOCTEXT("LyraHeroComponent", "NotOnPawnError", "has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint. This will cause a crash if you PIE!");
			static const FName HeroMessageLogName = TEXT("LyraHeroComponent");

			FMessageLog(HeroMessageLogName).Error()
				->AddToken(FUObjectToken::Create(this, FText::FromString(GetNameSafe(this))))
				->AddToken(FTextToken::Create(Message));

			FMessageLog(HeroMessageLogName).Open();
		}
#endif
	}
	else
	{
		// Register with the init state system early, this will only work if this is a game world
		RegisterInitStateFeature();
	}
}

void UG01HeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for when the pawn extension component changes init state
	BindOnActorInitStateChanged(UG01PawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// Notifies that we are done spawning, then try the rest of initialization
	ensure(TryToChangeInitState(G01GameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UG01HeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UG01HeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const UG01LocalPlayer* LP = Cast<UG01LocalPlayer>(PC->GetLocalPlayer());
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UG01PawnData* PawnData = PawnExtComp->GetPawnData<UG01PawnData>())
		{
			if (const UG01InputConfig* InputConfig = PawnData->InputConfig)
			{
				for (const FInputMappingContextAndPriority& Mapping : DefaultInputMappings)
				{
					if (UInputMappingContext* IMC = Mapping.InputMapping.LoadSynchronous())
					{
						if (Mapping.bRegisterWithSettings)
						{
							if (UEnhancedInputUserSettings* Settings = Subsystem->GetUserSettings())
							{
								Settings->RegisterInputMappingContext(IMC);
							}

							FModifyContextOptions Options = {};
							Options.bIgnoreAllPressedKeysUntilRelease = false;
							// Actually add the config to the local player							
							Subsystem->AddMappingContext(IMC, Mapping.Priority, Options);
						}
					}
				}

				// The Lyra Input Component has some additional functions to map Gameplay Tags to an Input Action.
				// If you want this functionality but still want to change your input component class, make it a subclass
				// of the ULyraInputComponent or modify this component accordingly.
				UG01InputComponent* IC = Cast<UG01InputComponent>(PlayerInputComponent);
				if (ensureMsgf(IC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to ULyraInputComponent or a subclass of it.")))
				{
					// Add the key mappings that may have been set by the player
					//IC->AddInputMappings(InputConfig, Subsystem);

					// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
					// be triggered directly by these input actions Triggered events. 
					TArray<uint32> BindHandles;
					IC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

					IC->BindNativeAction(InputConfig, G01GameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, /*bLogIfNotFound=*/ false);
					IC->BindNativeAction(InputConfig, G01GameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, /*bLogIfNotFound=*/ false);
					IC->BindNativeAction(InputConfig, G01GameplayTags::InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick, /*bLogIfNotFound=*/ false);
					IC->BindNativeAction(InputConfig, G01GameplayTags::InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, /*bLogIfNotFound=*/ false);
					IC->BindNativeAction(InputConfig, G01GameplayTags::InputTag_AutoRun, ETriggerEvent::Triggered, this, &ThisClass::Input_AutoRun, /*bLogIfNotFound=*/ false);
				}
			}
		}
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APlayerController*>(PC), NAME_BindInputsNow);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), NAME_BindInputsNow);
}
void UG01HeroComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (const UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			if (UG01AbilitySystemComponent* ASC = PawnExtComp->GetG01AbilitySystemComponent())
			{
				ASC->AbilityInputTagPressed(InputTag);
			}
		}
	}
}
void UG01HeroComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	if (const UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (UG01AbilitySystemComponent* ASC = PawnExtComp->GetG01AbilitySystemComponent())
		{
			ASC->AbilityInputTagReleased(InputTag);
		}
	}
}

