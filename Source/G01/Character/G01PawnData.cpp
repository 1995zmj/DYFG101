// Fill out your copyright notice in the Description page of Project Settings.


#include "G01PawnData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01PawnData)

UG01PawnData::UG01PawnData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnClass = nullptr;
	InputConfig = nullptr;
	DefaultCameraMode = nullptr;
}