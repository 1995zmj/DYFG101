

#pragma once

#include "CoreMinimal.h"
#include "G01TabListWidgetBase.h"
#include "UI/Foundation/G01ButtonBase.h"

#include "G01TabButtonBase.generated.h"

class UCommonLazyImage;

UCLASS(MinimalAPI, Abstract, Blueprintable, meta = (DisableNativeTick))
class UG01TabButtonBase : public UG01ButtonBase, public IG01TabButtonInterface
{
	GENERATED_BODY()

public:

	void SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject);
	void SetIconBrush(const FSlateBrush& Brush);

protected:

	UFUNCTION()
	virtual void SetTabLabelInfo_Implementation(const FG01TabDescriptor& TabLabelInfo) override;

private:

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonLazyImage> LazyImage_Icon;
};