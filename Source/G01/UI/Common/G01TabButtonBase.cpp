


#include "G01TabButtonBase.h"
#include "CommonLazyImage.h"
#include "G01TabListWidgetBase.h"


void UG01TabButtonBase::SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject)
{
	if (LazyImage_Icon)
	{
		LazyImage_Icon->SetBrushFromLazyDisplayAsset(LazyObject);
	}
}

void UG01TabButtonBase::SetIconBrush(const FSlateBrush& Brush)
{
	if (LazyImage_Icon)
	{
		LazyImage_Icon->SetBrush(Brush);
	}
}

void UG01TabButtonBase::SetTabLabelInfo_Implementation(const FG01TabDescriptor& TabLabelInfo)
{
	SetButtonText(TabLabelInfo.TabText);
	SetIconBrush(TabLabelInfo.IconBrush);
}

