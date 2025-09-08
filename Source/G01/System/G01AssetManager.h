// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "G01AssetManager.generated.h"

#define UE_API G01_API

struct FG01Bundles
{
	static const FName Equipped;
};


class UG01PawnData;

/**
 * 
 */
UCLASS(MinimalAPI, Config = Game)
class UG01AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UE_API UG01AssetManager& Get();

	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);


	const UG01PawnData* GetDefaultPawnData() const;


protected:
	/* 
	[/ Script / G01.G01LyraAssetManager]
	DefaultPawnData = / Game / Characters / Heroes / EmptyPawnData / DefaultPawnData_EmptyPawn.DefaultPawnData_EmptyPawn
	*/
	UPROPERTY(Config)
	TSoftObjectPtr<UG01PawnData> DefaultPawnData;
};

#undef UE_API

template<typename AssetType>
inline AssetType* UG01AssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	//const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	//if (AssetPath.IsValid())
	//{
	//	LoadedAsset = AssetPointer.Get();
	//	if (!LoadedAsset)
	//	{
	//		LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
	//		ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
	//	}

	//	if (LoadedAsset && bKeepInMemory)
	//	{
	//		// Added to loaded asset list.
	//		Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
	//	}
	//}

	return LoadedAsset;
}
