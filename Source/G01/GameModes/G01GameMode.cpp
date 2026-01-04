// Fill out your copyright notice in the Description page of Project Settings.


#include "G01GameMode.h"
#include "G01GameState.h"
#include "Kismet/GameplayStatics.h"
#include "G01ExperienceDefinition.h"
#include "G01WorldSettings.h"
#include "Player/G01PlayerController.h"
#include "Development/G01DeveloperSettings.h"
#include "System/G01AssetManager.h"
#include "G01LogChannels.h"
#include "G01ExperienceManagerComponent.h"
#include "Player/G01PlayerState.h"
#include "Character/G01PawnData.h"
#include "Character/G01Character.h"
#include "Character/G01PawnExtensionComponent.h"
#include "UI/G01HUD.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01GameMode)

AG01GameMode::AG01GameMode(const FObjectInitializer& ObjectInitializer)
{
	GameStateClass = AG01GameState::StaticClass();
	PlayerControllerClass = AG01PlayerController::StaticClass();
	PlayerStateClass = AG01PlayerState::StaticClass();
	DefaultPawnClass = AG01Character::StaticClass();
	HUDClass = AG01HUD::StaticClass();
}

const UG01PawnData* AG01GameMode::GetPawnDataForController(const AController* InController) const
{
	if (InController != nullptr)
	{
		if (const AG01PlayerState* PS = InController->GetPlayerState<AG01PlayerState>())
		{
			if (const UG01PawnData* PawnData = PS->GetPawnData<UG01PawnData>())
			{
				return PawnData;
			}
		}
	}

	// If not, fall back to the the default for the current experience
	check(GameState);
	UG01ExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UG01ExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		const UG01ExperienceDefinition* Experience = ExperienceComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData != nullptr)
		{
			return Experience->DefaultPawnData;
		}

		// Experience is loaded and there's still no pawn data, fall back to the default for now
		return UG01AssetManager::Get().GetDefaultPawnData();
	}

	// Experience not loaded yet, so there is no pawn data to be had
	return nullptr;
}

void AG01GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void AG01GameMode::InitGameState()
{
	Super::InitGameState();

	UG01ExperienceManagerComponent * ExperienceComponent = GameState->FindComponentByClass<UG01ExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

UClass* AG01GameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const UG01PawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

APawn* AG01GameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (UG01PawnExtensionComponent* PawnExtComp = UG01PawnExtensionComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const UG01PawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					PawnExtComp->SetPawnData(PawnData);
				}
				else
				{
					UE_LOG(LogG01, Error, TEXT("Game mode was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(SpawnedPawn));
				}
			}

			SpawnedPawn->FinishSpawning(SpawnTransform);

			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogG01, Error, TEXT("Game mode was unable to spawn Pawn of class [%s] at [%s]."), *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
		}
	}
	else
	{
		UE_LOG(LogG01, Error, TEXT("Game mode was unable to spawn Pawn due to NULL pawn class."));
	}

	return nullptr;
}

void AG01GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// Delay starting new players until the experience has been loaded
	// (players who log in prior to that will be started by OnExperienceLoaded)
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

void AG01GameMode::OnExperienceLoaded(const UG01ExperienceDefinition* CurrentExperience)
{
	// Spawn any players that are already attached
	//@TODO: Here we're handling only *player* controllers, but in GetDefaultPawnClassForController_Implementation we skipped all controllers
	// GetDefaultPawnClassForController_Implementation might only be getting called for players anyways
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);
		if ((PC != nullptr) && (PC->GetPawn() == nullptr))
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
}

bool AG01GameMode::IsExperienceLoaded() const
{
	check(GameState);
	UG01ExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UG01ExperienceManagerComponent>();
	check(ExperienceComponent);

	return ExperienceComponent->IsExperienceLoaded();
}

void AG01GameMode::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource)
{
	if (ExperienceId.IsValid())
	{
		UE_LOG(LogExperience, Log, TEXT("Identified experience %s (Source: %s)"), *ExperienceId.ToString(), *ExperienceIdSource);

		UG01ExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UG01ExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->SetCurrentExperience(ExperienceId);
	}
	else
	{
		UE_LOG(LogExperience, Error, TEXT("Failed to identify experience, loading screen will stay up forever"));
	}
}

void AG01GameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	// 主要是确定 Experience 资源
	FPrimaryAssetId ExperienceId;
	FString ExperienceIdSource;

	// Precedence order (highest wins)
	//  - Matchmaking assignment (if present)
	//  - URL Options override
	//  - Developer Settings (PIE only)
	//  - Command Line override
	//  - World Settings
	//  - Dedicated server
	//  - Default experience

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid() && UGameplayStatics::HasOption(OptionsString, TEXT("Experience")))
	{
		const FString ExperienceFromOptions = UGameplayStatics::ParseOption(OptionsString, TEXT("Experience"));
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType(UG01ExperienceDefinition::StaticClass()->GetFName()), FName(*ExperienceFromOptions));
		ExperienceIdSource = TEXT("OptionsString");
	}

	// 编辑器相关后面再说（编辑器配置不了解）
	/*if (!ExperienceId.IsValid() && World->IsPlayInEditor())
	{
		ExperienceId = GetDefault<UG01DeveloperSettings>()->ExperienceOverride;
		ExperienceIdSource = TEXT("DeveloperSettings");
	}*/

	// see if the command line wants to set the experience
	if (!ExperienceId.IsValid())
	{
		FString ExperienceFromCommandLine;
		if (FParse::Value(FCommandLine::Get(), TEXT("Experience="), ExperienceFromCommandLine))
		{
			ExperienceId = FPrimaryAssetId::ParseTypeAndName(ExperienceFromCommandLine);
			if (!ExperienceId.PrimaryAssetType.IsValid())
			{
				ExperienceId = FPrimaryAssetId(FPrimaryAssetType(UG01ExperienceDefinition::StaticClass()->GetFName()), FName(*ExperienceFromCommandLine));
			}
			ExperienceIdSource = TEXT("CommandLine");
		}
	}

	// see if the world settings has a default experience
	if (!ExperienceId.IsValid())
	{
		if (AG01WorldSettings* TypedWorldSettings = Cast<AG01WorldSettings>(GetWorldSettings()))
		{
			ExperienceId = TypedWorldSettings->GetDefaultGameplayExperience();
			ExperienceIdSource = TEXT("WorldSettings");
		}
	}

	UG01AssetManager& AssetManager = UG01AssetManager::Get();
	FAssetData Dummy;
	if (ExperienceId.IsValid() && !AssetManager.GetPrimaryAssetData(ExperienceId, /*out*/ Dummy))
	{
		UE_LOG(LogExperience, Error, TEXT("EXPERIENCE: Wanted to use %s but couldn't find it, falling back to the default)"), *ExperienceId.ToString());
		ExperienceId = FPrimaryAssetId();
	}

	// Final fallback to the default experience
	if (!ExperienceId.IsValid())
	{
		// 网络相关后面再说
		//if (TryDedicatedServerLogin())
		//{
		//	// This will start to host as a dedicated server
		//	return;
		//}

		//@TODO: Pull this from a config setting or something
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("G01ExperienceDefinition"), FName("B_DefaultExperience"));
		ExperienceIdSource = TEXT("Default");
	}

	OnMatchAssignmentGiven(ExperienceId, ExperienceIdSource);
;}
