// Copyright Epic Games, Inc. All Rights Reserved.

#include "HydroErosionSimulate.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FHydroErosionSimulateModule"

void FHydroErosionSimulateModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin( TEXT("HydroErosionSimulate"))->GetBaseDir() , TEXT("Shaders") );
	UE_LOG(LogTemp , Warning , TEXT("Path is : %s") , *PluginShaderDir);
	AddShaderSourceDirectoryMapping(TEXT("/Plugins/HydroErosionSimulate/Shaders"), PluginShaderDir);
}

void FHydroErosionSimulateModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHydroErosionSimulateModule, HydroErosionSimulate)