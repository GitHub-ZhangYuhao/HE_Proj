// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HydroErosionSimulate/Public/GPUErodeComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGPUErodeComponent() {}
// Cross Module References
	HYDROEROSIONSIMULATE_API UClass* Z_Construct_UClass_UGPUErodeComponent_NoRegister();
	HYDROEROSIONSIMULATE_API UClass* Z_Construct_UClass_UGPUErodeComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_HydroErosionSimulate();
// End Cross Module References
	void UGPUErodeComponent::StaticRegisterNativesUGPUErodeComponent()
	{
	}
	UClass* Z_Construct_UClass_UGPUErodeComponent_NoRegister()
	{
		return UGPUErodeComponent::StaticClass();
	}
	struct Z_Construct_UClass_UGPUErodeComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGPUErodeComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_HydroErosionSimulate,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGPUErodeComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "GPUErodeComponent.h" },
		{ "ModuleRelativePath", "Public/GPUErodeComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGPUErodeComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGPUErodeComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGPUErodeComponent_Statics::ClassParams = {
		&UGPUErodeComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UGPUErodeComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGPUErodeComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGPUErodeComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGPUErodeComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGPUErodeComponent, 2899203937);
	template<> HYDROEROSIONSIMULATE_API UClass* StaticClass<UGPUErodeComponent>()
	{
		return UGPUErodeComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGPUErodeComponent(Z_Construct_UClass_UGPUErodeComponent, &UGPUErodeComponent::StaticClass, TEXT("/Script/HydroErosionSimulate"), TEXT("UGPUErodeComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGPUErodeComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
