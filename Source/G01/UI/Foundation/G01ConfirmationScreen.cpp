// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Foundation/G01ConfirmationScreen.h"
#include "CommonTextBlock.h"
#include "CommonRichTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "G01ButtonBase.h"
#include "CommonBorder.h"
#include "ICommonInputModule.h"

#if WITH_EDITOR
#include "CommonInputSettings.h"
#include "Editor/WidgetCompilerLog.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01ConfirmationScreen)

void UG01ConfirmationScreen::SetupDialog(UCommonGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback)
{
	Super::SetupDialog(Descriptor, ResultCallback);

	Text_Title->SetText(Descriptor->Header);
	RichText_Description->SetText(Descriptor->Body);

	EntryBox_Buttons->Reset<UG01ButtonBase>([](UG01ButtonBase& Button)
		{
			Button.OnClicked().Clear();
		});

	for (const FConfirmationDialogAction& Action : Descriptor->ButtonActions)
	{
		FDataTableRowHandle ActionRow;

		switch (Action.Result)
		{
		case ECommonMessagingResult::Confirmed:
			ActionRow = ICommonInputModule::GetSettings().GetDefaultClickAction();
			break;
		case ECommonMessagingResult::Declined:
			ActionRow = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case ECommonMessagingResult::Cancelled:
			ActionRow = CancelAction;
			break;
		default:
			ensure(false);
			continue;
		}

		UG01ButtonBase* Button = EntryBox_Buttons->CreateEntry<UG01ButtonBase>();
		Button->SetTriggeringInputAction(ActionRow);
		Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
		Button->SetButtonText(Action.OptionalDisplayText);
	}

	OnResultCallback = ResultCallback;
}

void UG01ConfirmationScreen::KillDialog()
{
	Super::KillDialog();
}

void UG01ConfirmationScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Border_TapToCloseZone->OnMouseButtonDownEvent.BindDynamic(this, &UG01ConfirmationScreen::HandleTapToCloseZoneMouseButtonDown);
}

void UG01ConfirmationScreen::CloseConfirmationWindow(ECommonMessagingResult Result)
{
	DeactivateWidget();
	OnResultCallback.ExecuteIfBound(Result);
}

FEventReply UG01ConfirmationScreen::HandleTapToCloseZoneMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = FReply::Unhandled();

	if (MouseEvent.IsTouchEvent() || MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		CloseConfirmationWindow(ECommonMessagingResult::Declined);
		Reply.NativeReply = FReply::Handled();
	}

	return Reply;
}

#if WITH_EDITOR
void UG01ConfirmationScreen::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	if (CancelAction.IsNull())
	{
		CompileLog.Error(FText::Format(FText::FromString(TEXT("{0} has unset property: CancelAction.")), FText::FromString(GetName())));
	}
}
#endif
