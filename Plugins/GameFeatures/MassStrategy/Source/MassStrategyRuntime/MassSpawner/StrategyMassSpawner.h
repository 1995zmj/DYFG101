#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MassSpawner.h"
#include "StrategyMassSpawner.generated.h"


USTRUCT(BlueprintType)
struct FMonsterConfig
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMassSpawnedEntityType EntityType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Count;
};

USTRUCT(BlueprintType)
struct FWaveConfig
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FMonsterConfig> MonsterConfigs;
};

UCLASS(abstract)
class AStrategyMassSpawner : public AMassSpawner
{
	GENERATED_BODY()
public:
	AStrategyMassSpawner();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wave Spawner")
	TArray<FWaveConfig> WaveConfigs;

	UPROPERTY(EditAnywhere, Category = "Wave Spawner", meta = (ClampMin = 0, ClampMax = 20, Units = "s"))
	float SpawnDelay = 3.0f;

	UPROPERTY()
	bool isReady = false;

private:
	/** NPC group spawn timer */
	FTimerHandle SpawnGroupTimer;

	/** NPC spawn timer */
	FTimerHandle SpawnNPCTimer;

	int CurWaveIndex = -1;

public:
	UFUNCTION(BlueprintCallable)
	void ReadWave();

	UFUNCTION(BlueprintCallable)
	void StartWave(int WaveIndex);

private:
	void SpawnItem();

};
