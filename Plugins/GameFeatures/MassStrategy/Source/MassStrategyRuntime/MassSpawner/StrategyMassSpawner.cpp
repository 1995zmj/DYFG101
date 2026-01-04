


#include "StrategyMassSpawner.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "MassEntityConfigAsset.h"
#include "Engine/World.h"
#include "MassSpawnerSubsystem.h"
#include "MassSpawnLocationProcessor.h"

AStrategyMassSpawner::AStrategyMassSpawner()
{
	bAutoSpawnOnBeginPlay = false;
	bOverrideSchematics = false;
}

void AStrategyMassSpawner::ReadWave()
{
	if (WaveConfigs.Num() == 0)
	{
		//UE_VLOG_UELOG(this, LogMassSpawner, Warning, TEXT("No Spawn Data Generators configured."));
		return;
	}

	TArray<FSoftObjectPath> AssetsToLoad;
	for (const FWaveConfig& Wave : WaveConfigs)
	{
		for (const FMonsterConfig& MonsterConfig : Wave.MonsterConfigs)
		{
			if (!MonsterConfig.EntityType.IsLoaded())
			{
				AssetsToLoad.Add(MonsterConfig.EntityType.EntityConfig.ToSoftObjectPath());
			}
		}
		
	}


	auto GenerateSpawningPoints = [this]()
	{
			isReady = true;
	};

	if (AssetsToLoad.Num())
	{
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		StreamingHandle = StreamableManager.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateWeakLambda(this, GenerateSpawningPoints));
	}
	else
	{
		GenerateSpawningPoints();
	}
}

void AStrategyMassSpawner::StartWave(int WaveIndex)
{
	if (!isReady)
	{
		//UE_VLOG_UELOG(this, LogMassSpawner, Warning, TEXT("WaveConfigs not ready."));
		return;
	}
	if (WaveIndex >= WaveConfigs.Num())
	{
		//UE_VLOG_UELOG(this, LogMassSpawner, Warning, TEXT("WaveConfigs not WaveIndex"));
		return;
	}

	CurWaveIndex = WaveIndex;
	GetWorld()->GetTimerManager().SetTimer(SpawnGroupTimer, this, &AStrategyMassSpawner::SpawnItem, SpawnDelay, false);
}

void AStrategyMassSpawner::SpawnItem()
{
	UMassSpawnerSubsystem* SpawnerSystem = UWorld::GetSubsystem<UMassSpawnerSubsystem>(GetWorld());
	if (SpawnerSystem == nullptr)
	{
		//UE_VLOG_UELOG(this, LogMassSpawner, Error, TEXT("UMassSpawnerSubsystem missing while trying to spawn entities"));
		return;
	}
	UWorld* World = GetWorld();
	const FMassSpawnedEntityType& EntityType = WaveConfigs[CurWaveIndex].MonsterConfigs[0].EntityType;


	int TotalNum = 1;
	FInstancedStruct SpawnData;
	SpawnData.InitializeAs<FMassTransformsSpawnData>();
	FMassTransformsSpawnData& Transforms = SpawnData.GetMutable<FMassTransformsSpawnData>();
	Transforms.Transforms.Reserve(TotalNum);
	for (int i = 0; i < TotalNum; i++)
	{
		FTransform& Transform = Transforms.Transforms.AddDefaulted_GetRef();
		Transform.SetLocation(GetActorLocation());
	}
	TSubclassOf<UMassProcessor> SpawnDataProcessor = UMassSpawnLocationProcessor::StaticClass();


	if (const UMassEntityConfigAsset* EntityConfig = EntityType.GetEntityConfig())
	{
		const FMassEntityTemplate& EntityTemplate = EntityConfig->GetOrCreateEntityTemplate(*World);
		if (EntityTemplate.IsValid())
		{
			FSpawnedEntities& SpawnedEntities = AllSpawnedEntities.AddDefaulted_GetRef();
			SpawnedEntities.TemplateID = EntityTemplate.GetTemplateID();
			SpawnerSystem->SpawnEntities(EntityTemplate.GetTemplateID(), TotalNum, SpawnData, SpawnDataProcessor, SpawnedEntities.Entities);
			//TotalNum += SpawnedEntities.Entities.Num();
		}
	}
}
