// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"

#include "G01GameInstance.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Config = Game)
class UG01GameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

};
