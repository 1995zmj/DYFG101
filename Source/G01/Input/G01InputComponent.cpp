// Fill out your copyright notice in the Description page of Project Settings.


#include "G01InputComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(G01InputComponent)


UG01InputComponent::UG01InputComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UG01InputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
