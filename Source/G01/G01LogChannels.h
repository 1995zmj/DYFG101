// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"

G01_API DECLARE_LOG_CATEGORY_EXTERN(LogExperience, Log, All);
G01_API DECLARE_LOG_CATEGORY_EXTERN(LogG01, Log, All);
G01_API DECLARE_LOG_CATEGORY_EXTERN(LogG01AbilitySystem, Log, All);


G01_API FString GetClientServerContextString(UObject* ContextObject = nullptr);