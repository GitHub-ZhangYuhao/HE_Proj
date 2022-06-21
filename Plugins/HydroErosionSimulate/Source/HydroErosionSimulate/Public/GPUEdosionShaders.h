#pragma once

#include "CoreMinimal.h"
#include "ShaderParameterStruct.h"

class FSimulateBaseShader: public FGlobalShader
{
public:
	static int ThreadSize = 32;
	DECLARE_GLOBAL_SHADER(FSimulateBaseShader)
	SHADER_USE_PARAMETER_STRUCT(FSimulateBaseShader , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters , )
	END_SHADER_PARAMETER_STRUCT()
};

class FInitSimuData: public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FInitSimuData)
	SHADER_USE_PARAMETER_STRUCT(FInitSimuData , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters , )	
		SHADER_PARAMETER_TEXTURE(Texture2D , InHeightMapTex)
		SHADER_PARAMETER_SAMPLER(SamplerState , InHeightMapTexSampler)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4> ,SimulateTex)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer , FluxBufferW)
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