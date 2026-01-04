// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/CommonBoundActionButton.h"
#include "G01BoundActionButton.generated.h"

class UCommonButtonStyle;
class UObject;

UCLASS(MinimalAPI, Abstract, meta = (DisableNativeTick))
class UG01BoundActionButton : public UCommonBoundActionButton
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	void HandleInputMethodChanged(ECommonInputType NewInputMethod);

	UPROPERTY(EditAnywhere, Category = "Styles")
	TSubclassOf<UCommonButtonStyle> KeyboardStyle;

	UPROPERTY(EditAnywhere, Category = "Styles")
	TSubclassOf<UCommonButtonStyle> GamepadStyle;

	UPROPERTY(EditAnywhere, Category = "Styles")
	TSubclassOf<UCommonButtonStyle> TouchStyle;
};