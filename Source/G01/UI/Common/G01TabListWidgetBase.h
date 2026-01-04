// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "G01TabListWidgetBase.generated.h"

USTRUCT(BlueprintType)
struct FG01TabDescriptor
{
	GENERATED_BODY()

public:
	FG01TabDescriptor()
		: bHidden(false)
		, CreatedTabContentWidget(nullptr)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName TabId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush IconBrush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHidden;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCommonButtonBase> TabButtonType;

	//TODO NDarnell - This should become a TSoftClassPtr<>, the underlying common tab list needs to be able to handle lazy tab content construction.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCommonUserWidget> TabContentType;

	UPROPERTY(Transient)
	TObjectPtr<UWidget> CreatedTabContentWidget;
};

UINTERFACE(BlueprintType)
class UG01TabButtonInterface : public UInterface
{
	GENERATED_BODY()
};

class IG01TabButtonInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Tab Button")
	void SetTabLabelInfo(const FG01TabDescriptor& TabDescriptor);
};

UCLASS(MinimalAPI, Blueprintable, BlueprintType, Abstract, meta = (DisableNativeTick))
class UG01TabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	bool GetPreregisteredTabInfo(const FName TabNameId, FG01TabDescriptor& OutTabInfo);

	/** Helper method to get at all the preregistered tab infos */
	const TArray<FG01TabDescriptor>& GetAllPreregisteredTabInfos() { return PreregisteredTabInfoArray; }

	// Toggles whether or not a specified tab is hidden, can only be called before the switcher is associated
	UFUNCTION(BlueprintCallable, Category = "Tab List")
	void SetTabHiddenState(FName TabNameId, bool bHidden);

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool RegisterDynamicTab(const FG01TabDescriptor& TabDescriptor);

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool IsFirstTabActive() const;

	UFUNCTION(BlueprintCallable, Category = "Tab List")
	bool IsLastTabActive() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	bool IsTabVisible(FName TabId);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
	int32 GetVisibleTabCount();

	/** Delegate broadcast when a new tab is created. Allows hook ups after creation. */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabContentCreated, FName, TabId, UCommonUserWidget*, TabWidget);
	DECLARE_EVENT_TwoParams(UG01TabListWidgetBase, FOnTabContentCreatedNative, FName /* TabId */, UCommonUserWidget* /* TabWidget */);

	/** Broadcasts when a new tab is created. */
	UPROPERTY(BlueprintAssignable, Category = "Tab List")
	FOnTabContentCreated OnTabContentCreated;
	FOnTabContentCreatedNative OnTabContentCreatedNative;

protected:
	// UUserWidget interface
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget

	virtual void HandlePreLinkedSwitcherChanged() override;
	virtual void HandlePostLinkedSwitcherChanged() override;

	virtual void HandleTabCreation_Implementation(FName TabId, UCommonButtonBase* TabButton) override;

private:
	void SetupTabs();

	UPROPERTY(EditAnywhere, meta = (TitleProperty = "TabId"))
	TArray<FG01TabDescriptor> PreregisteredTabInfoArray;

	/**
	 * Stores label info for tabs that have been registered at runtime but not yet created.
	 * Elements are removed once they are created.
	 */
	UPROPERTY()
	TMap<FName, FG01TabDescriptor> PendingTabLabelInfoMap;
	
};
