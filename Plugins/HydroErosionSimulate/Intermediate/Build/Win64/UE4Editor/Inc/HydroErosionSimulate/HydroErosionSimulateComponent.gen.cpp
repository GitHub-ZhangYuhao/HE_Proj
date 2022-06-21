// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "HydroErosionSimulate/Public/HydroErosionSimulateComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHydroErosionSimulateComponent() {}
// Cross Module References
	HYDROEROSIONSIMULATE_API UClass* Z_Construct_UClass_UHydroErosionSimulateComponent_NoRegister();
	HYDROEROSIONSIMULATE_API UClass* Z_Construct_UClass_UHydroErosionSimulateComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_HydroErosionSimulate();
	ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	DEFINE_FUNCTION(UHydroErosionSimulateComponent::execSimulateHydroErosion_RenderThread)
	{
		P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_InRenderTarget);
		P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_DebugRenderTarget);
		P_GET_STRUCT(FVector,Z_Param_WaterData);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SimulateHydroErosion_RenderThread(Z_Param_InRenderTarget,Z_Param_DebugRenderTarget,Z_Param_WaterData);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHydroErosionSimulateComponent::execInitSimuData_RenderThread)
	{
		P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_InRenderTarget);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitSimuData_RenderThread(Z_Param_InRenderTarget);
		P_NATIVE_END;
	}
	void UHydroErosionSimulateComponent::StaticRegisterNativesUHydroErosionSimulateComponent()
	{
		UClass* Class = UHydroErosionSimulateComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "InitSimuData_RenderThread", &UHydroErosionSimulateComponent::execInitSimuData_RenderThread },
			{ "SimulateHydroErosion_RenderThread", &UHydroErosionSimulateComponent::execSimulateHydroErosion_RenderThread },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics
	{
		struct HydroErosionSimulateComponent_eventInitSimuData_RenderThread_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::NewProp_InRenderTarget = { "InRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HydroErosionSimulateComponent_eventInitSimuData_RenderThread_Parms, InRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::NewProp_InRenderTarget,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::Function_MetaDataParams[] = {
		{ "Category", "HydroSimu" },
		{ "Comment", "//\xe9\x80\x9f\xe5\xba\xa6\xe7\x9f\xa2\xe9\x87\x8f\x09:float2 (u,v)\n" },
		{ "ModuleRelativePath", "Public/HydroErosionSimulateComponent.h" },
		{ "ToolTip", "\xe9\x80\x9f\xe5\xba\xa6\xe7\x9f\xa2\xe9\x87\x8f    :float2 (u,v)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHydroErosionSimulateComponent, nullptr, "InitSimuData_RenderThread", nullptr, nullptr, sizeof(HydroErosionSimulateComponent_eventInitSimuData_RenderThread_Parms), Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics
	{
		struct HydroErosionSimulateComponent_eventSimulateHydroErosion_RenderThread_Parms
		{
			UTextureRenderTarget2D* InRenderTarget;
			UTextureRenderTarget2D* DebugRenderTarget;
			FVector WaterData;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_InRenderTarget;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DebugRenderTarget;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WaterData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::NewProp_InRenderTarget = { "InRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HydroErosionSimulateComponent_eventSimulateHydroErosion_RenderThread_Parms, InRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::NewProp_DebugRenderTarget = { "DebugRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HydroErosionSimulateComponent_eventSimulateHydroErosion_RenderThread_Parms, DebugRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::NewProp_WaterData = { "WaterData", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HydroErosionSimulateComponent_eventSimulateHydroErosion_RenderThread_Parms, WaterData), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::NewProp_InRenderTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::NewProp_DebugRenderTarget,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::NewProp_WaterData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::Function_MetaDataParams[] = {
		{ "Category", "HydroSimu" },
		{ "ModuleRelativePath", "Public/HydroErosionSimulateComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHydroErosionSimulateComponent, nullptr, "SimulateHydroErosion_RenderThread", nullptr, nullptr, sizeof(HydroErosionSimulateComponent_eventSimulateHydroErosion_RenderThread_Parms), Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UHydroErosionSimulateComponent_NoRegister()
	{
		return UHydroErosionSimulateComponent::StaticClass();
	}
	struct Z_Construct_UClass_UHydroErosionSimulateComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThreadSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ThreadSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WaterSimuData_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WaterSimuData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_HydroErosionSimulate,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHydroErosionSimulateComponent_InitSimuData_RenderThread, "InitSimuData_RenderThread" }, // 1445302303
		{ &Z_Construct_UFunction_UHydroErosionSimulateComponent_SimulateHydroErosion_RenderThread, "SimulateHydroErosion_RenderThread" }, // 2312873353
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "HydroErosionSimulateComponent.h" },
		{ "ModuleRelativePath", "Public/HydroErosionSimulateComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_ThreadSize_MetaData[] = {
		{ "Category", "HydroErosionSimulateComponent" },
		{ "Comment", "/*\n\x09Terrain Height\x09: B\n\x09Water Height\x09: D\n\x09Sediment\x09\x09: S\n\x09OutFlux\x09\x09\x09: F\n\x09VelocityVec\x09\x09: V\n\x09*/" },
		{ "ModuleRelativePath", "Public/HydroErosionSimulateComponent.h" },
		{ "ToolTip", "Terrain Height  : B\nWater Height    : D\nSediment                : S\nOutFlux                 : F\nVelocityVec             : V" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_ThreadSize = { "ThreadSize", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHydroErosionSimulateComponent, ThreadSize), METADATA_PARAMS(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_ThreadSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_ThreadSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_WaterSimuData_MetaData[] = {
		{ "Category", "HydroErosionSimulateComponent" },
		{ "ModuleRelativePath", "Public/HydroErosionSimulateComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_WaterSimuData = { "WaterSimuData", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UHydroErosionSimulateComponent, WaterSimuData), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_WaterSimuData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_WaterSimuData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_ThreadSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::NewProp_WaterSimuData,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHydroErosionSimulateComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::ClassParams = {
		&UHydroErosionSimulateComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHydroErosionSimulateComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHydroErosionSimulateComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHydroErosionSimulateComponent, 2496000698);
	template<> HYDROEROSIONSIMULATE_API UClass* StaticClass<UHydroErosionSimulateComponent>()
	{
		return UHydroErosionSimulateComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHydroErosionSimulateComponent(Z_Construct_UClass_UHydroErosionSimulateComponent, &UHydroErosionSimulateComponent::StaticClass, TEXT("/Script/HydroErosionSimulate"), TEXT("UHydroErosionSimulateComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHydroErosionSimulateComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
