// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/G01SettingScreen.h"
#include "Player/G01LocalPlayer.h"
#include "Settings/G01GameSettingRegistry.h"
#include "Input/CommonUIInputTypes.h"

void UG01SettingScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackAction)));
	ApplyHandle = RegisterUIActionBinding(FBindUIActionArgs(ApplyInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleApplyAction)));
	CancelChangesHandle = RegisterUIActionBinding(FBindUIActionArgs(CancelChangesInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleCancelChangesAction)));
}

UGameSettingRegistry* UG01SettingScreen::CreateRegistry()
{
	UG01GameSettingRegistry* NewRegistry = NewObject<UG01GameSettingRegistry>();

	if (UG01LocalPlayer* LocalPlayer = CastChecked<UG01LocalPlayer>(GetOwningLocalPlayer()))
	{
		NewRegistry->Initialize(LocalPlayer);
	}

	return NewRegistry;
}

void UG01SettingScreen::HandleBackAction()
{
	if (AttemptToPopNavigation())
	{
		return;
	}

	ApplyChanges();

	DeactivateWidget();
}

void UG01SettingScreen::HandleApplyAction()
{
	ApplyChanges();
}

void UG01SettingScreen::HandleCancelChangesAction()
{
	CancelChanges();
}

void UG01SettingScreen::OnSettingsDirtyStateChanged_Implementation(bool bSettingsDirty)
{
	if (bSettingsDirty)
	{
		if (!GetActionBindings().Contains(ApplyHandle))
		{
			AddActionBinding(ApplyHandle);
		}
		if (!GetActionBindings().Contains(CancelChangesHandle))
		{
			AddActionBinding(CancelChangesHandle);
		}
	}
	else
	{
		RemoveActionBinding(ApplyHandle);
		RemoveActionBinding(CancelChangesHandle);
	}
}


