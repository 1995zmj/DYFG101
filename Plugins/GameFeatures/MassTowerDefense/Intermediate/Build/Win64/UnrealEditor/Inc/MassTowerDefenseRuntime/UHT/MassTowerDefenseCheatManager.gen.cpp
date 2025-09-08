// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MassTowerDefenseCheatManager.h"
#include "GameFramework/CheatManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeMassTowerDefenseCheatManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UCheatManagerExtension();
MASSTOWERDEFENSERUNTIME_API UClass* Z_Construct_UClass_UMassTowerDefenseCheatManager();
MASSTOWERDEFENSERUNTIME_API UClass* Z_Construct_UClass_UMassTowerDefenseCheatManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_MassTowerDefenseRuntime();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMassTowerDefenseCheatManager Function TestString ************************
struct Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/MassTowerDefenseCheatManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UMassTowerDefenseCheatManager, nullptr, "TestString", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020601, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UMassTowerDefenseCheatManager::execTestString)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TestString();
	P_NATIVE_END;
}
// ********** End Class UMassTowerDefenseCheatManager Function TestString **************************

// ********** Begin Class UMassTowerDefenseCheatManager ********************************************
void UMassTowerDefenseCheatManager::StaticRegisterNativesUMassTowerDefenseCheatManager()
{
	UClass* Class = UMassTowerDefenseCheatManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "TestString", &UMassTowerDefenseCheatManager::execTestString },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UMassTowerDefenseCheatManager;
UClass* UMassTowerDefenseCheatManager::GetPrivateStaticClass()
{
	using TClass = UMassTowerDefenseCheatManager;
	if (!Z_Registration_Info_UClass_UMassTowerDefenseCheatManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("MassTowerDefenseCheatManager"),
			Z_Registration_Info_UClass_UMassTowerDefenseCheatManager.InnerSingleton,
			StaticRegisterNativesUMassTowerDefenseCheatManager,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UMassTowerDefenseCheatManager.InnerSingleton;
}
UClass* Z_Construct_UClass_UMassTowerDefenseCheatManager_NoRegister()
{
	return UMassTowerDefenseCheatManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "IncludePath", "MassTowerDefenseCheatManager.h" },
		{ "ModuleRelativePath", "Public/MassTowerDefenseCheatManager.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UMassTowerDefenseCheatManager_TestString, "TestString" }, // 640811754
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMassTowerDefenseCheatManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCheatManagerExtension,
	(UObject* (*)())Z_Construct_UPackage__Script_MassTowerDefenseRuntime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics::ClassParams = {
	&UMassTowerDefenseCheatManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMassTowerDefenseCheatManager()
{
	if (!Z_Registration_Info_UClass_UMassTowerDefenseCheatManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMassTowerDefenseCheatManager.OuterSingleton, Z_Construct_UClass_UMassTowerDefenseCheatManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMassTowerDefenseCheatManager.OuterSingleton;
}
UMassTowerDefenseCheatManager::UMassTowerDefenseCheatManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMassTowerDefenseCheatManager);
UMassTowerDefenseCheatManager::~UMassTowerDefenseCheatManager() {}
// ********** End Class UMassTowerDefenseCheatManager **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_DYF_DYFG101_Plugins_GameFeatures_MassTowerDefense_Source_MassTowerDefenseRuntime_Public_MassTowerDefenseCheatManager_h__Script_MassTowerDefenseRuntime_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMassTowerDefenseCheatManager, UMassTowerDefenseCheatManager::StaticClass, TEXT("UMassTowerDefenseCheatManager"), &Z_Registration_Info_UClass_UMassTowerDefenseCheatManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMassTowerDefenseCheatManager), 3091842291U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_DYF_DYFG101_Plugins_GameFeatures_MassTowerDefense_Source_MassTowerDefenseRuntime_Public_MassTowerDefenseCheatManager_h__Script_MassTowerDefenseRuntime_3412325235(TEXT("/Script/MassTowerDefenseRuntime"),
	Z_CompiledInDeferFile_FID_DYF_DYFG101_Plugins_GameFeatures_MassTowerDefense_Source_MassTowerDefenseRuntime_Public_MassTowerDefenseCheatManager_h__Script_MassTowerDefenseRuntime_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_DYF_DYFG101_Plugins_GameFeatures_MassTowerDefense_Source_MassTowerDefenseRuntime_Public_MassTowerDefenseCheatManager_h__Script_MassTowerDefenseRuntime_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
