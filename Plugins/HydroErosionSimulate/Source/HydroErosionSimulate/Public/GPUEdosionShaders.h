#pragma once

#include "CoreMinimal.h"
#include "ShaderParameterStruct.h"

/*
class FSimulateBaseShader: public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FSimulateBaseShader)
	SHADER_USE_PARAMETER_STRUCT(FSimulateBaseShader , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters , )
	END_SHADER_PARAMETER_STRUCT()
};
*/

class FInitSimuData: public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FInitSimuData)
	SHADER_USE_PARAMETER_STRUCT(FInitSimuData , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters , )	
		SHADER_PARAMETER_TEXTURE(Texture2D , InHeightMapTex)
		SHADER_PARAMETER_SAMPLER(SamplerState , InHeightMapTexSampler)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4> ,SimulateTexW)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FVector4> , FluxW)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FVector2f> , VelocityW)
	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(FGlobalShaderPermutationParameters const& Parameters)
	{
		return RHISupportsComputeShaders(Parameters.Platform);
	}
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//OutEnvironment.SetDefine();
	}
};
IMPLEMENT_GLOBAL_SHADER(FInitSimuData, "/Plugins/HydroErosionSimulate/Shaders/Private/GPUErosionSimulate.usf" , "InitSimuData", SF_Compute);

class FUpdateWaterAndHeightCS: public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FUpdateWaterAndHeightCS)
	SHADER_USE_PARAMETER_STRUCT(FUpdateWaterAndHeightCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters , )
		SHADER_PARAMETER(FVector , RainData)
		SHADER_PARAMETER_TEXTURE(Texture2D , SimulateTexR)
		SHADER_PARAMETER_SAMPLER(SamplerState , SimulateTexSampler)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4> ,SimulateTexW)
	END_SHADER_PARAMETER_STRUCT()
	
	static bool ShouldCompilePermutation(FGlobalShaderPermutationParameters const& Parameters)
	{
		return RHISupportsComputeShaders(Parameters.Platform);
	}
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//OutEnvironment.SetDefine();
	}
};
IMPLEMENT_GLOBAL_SHADER(FUpdateWaterAndHeightCS, "/Plugins/HydroErosionSimulate/Shaders/Private/GPUErosionSimulate.usf" , "UpdateWaterAndHeightCS", SF_Compute);

class FOutFluxComputeCS:public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FOutFluxComputeCS)
	SHADER_USE_PARAMETER_STRUCT(FOutFluxComputeCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters , )
		SHADER_PARAMETER_TEXTURE(Texture2D , SimulateTexR)
		SHADER_PARAMETER_SAMPLER(SamplerState , SimulateTexSampler)
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float4> ,FluxR)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float4> , FluxW)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWStructuredBuffer<float4> ,DebugTex)
	END_SHADER_PARAMETER_STRUCT()
	
	static bool ShouldCompilePermutation(FGlobalShaderPermutationParameters const& Parameters)
	{
		return RHISupportsComputeShaders(Parameters.Platform);
	}
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//OutEnvironment.SetDefine();
	}
};
IMPLEMENT_GLOBAL_SHADER(FOutFluxComputeCS, "/Plugins/HydroErosionSimulate/Shaders/Private/GPUErosionSimulate.usf" , "OutFluxComputeCS", SF_Compute);
