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
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	DEFINE_FUNCTION(UGPUErodeComponent::execInvokeGPUErosion_RenderThread)
	{
		P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_InRenderTarget);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InvokeGPUErosion_RenderThread(Z_Param_InRenderTarget);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGPUErodeComponent::execInvokeGPUInitData_RenderThread)
	{
		P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_InRenderTarget);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InvokeGPUInitData_RenderThread(Z_Param_InRenderTarget);
		P_NATIVE_END;
	}
	void UGPUErodeComponent::StaticRegisterNativesUGPUErodeComponent()
	{
		UClass* Class = UGPUErodeComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "InvokeGPUErosion_RenderThread", &UGPUErodeComponent::execInvokeGPUErosion_RenderThread },
			{ "InvokeGPUInitData_RenderThread", &UGPUErodeComponent::execInvokeGPUInitData_RenderThread },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics
	{
		struct GPUErodeComponent_eventInvokeGPUErosion_RenderThread_Parms
		{
			UTextureRenderTarget2D* InRenderTarget;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InRenderTarget;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::NewProp_InRenderTarget = { "InRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GPUErodeComponent_eventInvokeGPUErosion_RenderThread_Parms, InRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::NewProp_InRenderTarget,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::Function_MetaDataParams[] = {
		{ "Category", "GPUHydroErosion" },
		{ "ModuleRelativePath", "Public/GPUErodeComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUErodeComponent, nullptr, "InvokeGPUErosion_RenderThread", nullptr, nullptr, sizeof(GPUErodeComponent_eventInvokeGPUErosion_RenderThread_Parms), Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics
	{
		struct GPUErodeComponent_eventInvokeGPUInitData_RenderThread_Parms
		{
			UTextureRenderTarget2D* InRenderTarget;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InRenderTarget;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::NewProp_InRenderTarget = { "InRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GPUErodeComponent_eventInvokeGPUInitData_RenderThread_Parms, InRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::NewProp_InRenderTarget,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::Function_MetaDataParams[] = {
		{ "Category", "GPUHydroErosion" },
		{ "ModuleRelativePath", "Public/GPUErodeComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGPUErodeComponent, nullptr, "InvokeGPUInitData_RenderThread", nullptr, nullptr, sizeof(GPUErodeComponent_eventInvokeGPUInitData_RenderThread_Parms), Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGPUErodeComponent_NoRegister()
	{
		return UGPUErodeComponent::StaticClass();
	}
	struct Z_Construct_UClass_UGPUErodeComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RainData_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RainData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGPUErodeComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_HydroErosionSimulate,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGPUErodeComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUErosion_RenderThread, "InvokeGPUErosion_RenderThread" }, // 1024067669
		{ &Z_Construct_UFunction_UGPUErodeComponent_InvokeGPUInitData_RenderThread, "InvokeGPUInitData_RenderThread" }, // 2535168111
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGPUErodeComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "GPUErodeComponent.h" },
		{ "ModuleRelativePath", "Public/GPUErodeComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGPUErodeComponent_Statics::NewProp_RainData_MetaData[] = {
		{ "Category", "GPUErodeComponent" },
		{ "Comment", "//SimulateData\n" },
		{ "ModuleRelativePath", "Public/GPUErodeComponent.h" },
		{ "ToolTip", "SimulateData" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGPUErodeComponent_Statics::NewProp_RainData = { "RainData", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGPUErodeComponent, RainData), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UGPUErodeComponent_Statics::NewProp_RainData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGPUErodeComponent_Statics::NewProp_RainData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGPUErodeComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGPUErodeComponent_Statics::NewProp_RainData,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGPUErodeComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGPUErodeComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGPUErodeComponent_Statics::ClassParams = {
		&UGPUErodeComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGPUErodeComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGPUErodeComponent_Statics::PropPointers),
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
	IMPLEMENT_CLASS(UGPUErodeComponent, 4017464306);
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
