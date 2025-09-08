// Fill out your copyright notice in the Description page of Project Settings.


#include "G01AssetManager.h"
#include "G01LogChannels.h"

const FName FG01Bundles::Equipped("Equipped");

UG01AssetManager& UG01AssetManager::Get()
{
	check(GEngine);

	if (UG01AssetManager* Singleton = Cast<UG01AssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogG01, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini.  It must be set to LyraAssetManager!"));

	// Fatal error above prevents this from being called.
	return *NewObject<UG01AssetManager>();
}

const UG01PawnData* UG01AssetManager::GetDefaultPawnData() const
{
	return GetAsset(DefaultPawnData);
}
