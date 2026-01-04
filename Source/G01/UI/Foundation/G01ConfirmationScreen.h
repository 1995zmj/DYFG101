// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Messaging/CommonGameDialog.h"
#include "G01ConfirmationScreen.generated.h"

class UCommonTextBlock;
class UCommonRichTextBlock;
class UDynamicEntryBox;
class UCommonBorder;

UCLASS(Abstract, BlueprintType, Blueprintable)
class G01_API UG01ConfirmationScreen : public UCommonGameDialog
{
	GENERATED_BODY()
	
	
public:
	virtual void SetupDialog(UCommonGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback) override;
	virtual void KillDialog() override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void CloseConfirmationWindow(ECommonMessagingResult Result);

#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif

private:

	UFUNCTION()
	FEventReply HandleTapToCloseZoneMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	FCommonMessagingResultDelegate OnResultCallback;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Text_Title;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCommonRichTextBlock> RichText_Description;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> EntryBox_Buttons;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UCommonBorder> Border_TapToCloseZone;

	UPROPERTY(EditDefaultsOnly, meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle CancelAction;
};
