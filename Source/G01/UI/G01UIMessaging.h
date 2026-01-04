// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"
#include "Messaging/CommonMessagingSubsystem.h"
#include "G01UIMessaging.generated.h"

class FSubsystemCollectionBase;
class UCommonGameDialog;
class UCommonGameDialogDescriptor;
class UObject;

UCLASS()
class UG01UIMessaging : public UCommonMessagingSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void ShowConfirmation(UCommonGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate()) override;
	virtual void ShowError(UCommonGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate()) override;

private:
	UPROPERTY()
	TSubclassOf<UCommonGameDialog> ConfirmationDialogClassPtr;

	UPROPERTY()
	TSubclassOf<UCommonGameDialog> ErrorDialogClassPtr;

	UPROPERTY(config)
	TSoftClassPtr<UCommonGameDialog> ConfirmationDialogClass;

	UPROPERTY(config)
	TSoftClassPtr<UCommonGameDialog> ErrorDialogClass;
	
};
