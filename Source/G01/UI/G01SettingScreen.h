// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Widgets/GameSettingScreen.h"
#include "G01SettingScreen.generated.h"


class UG01TabListWidgetBase;


UCLASS(Abstract, meta = (Category = "Settings", DisableNativeTick))
class G01_API UG01SettingScreen : public UGameSettingScreen
{
	GENERATED_BODY()
	
public:

protected:
	virtual void NativeOnInitialized() override;
	virtual UGameSettingRegistry* CreateRegistry() override;

	void HandleBackAction();
	void HandleApplyAction();
	void HandleCancelChangesAction();

	virtual void OnSettingsDirtyStateChanged_Implementation(bool bSettingsDirty) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (BindWidget, OptionalWidget = true, AllowPrivateAccess = true))
	TObjectPtr<UG01TabListWidgetBase> TopSettingsTabs;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle BackInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle ApplyInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle CancelChangesInputActionData;

	FUIActionBindingHandle BackHandle;
	FUIActionBindingHandle ApplyHandle;
	FUIActionBindingHandle CancelChangesHandle;
	
};
