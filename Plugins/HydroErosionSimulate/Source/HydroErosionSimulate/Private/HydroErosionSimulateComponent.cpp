// Fill out your copyright notice in the Description page of Project Settings.


#include "HydroErosionSimulateComponent.h"

#include "RenderGraphUtils.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values for this component's properties
UHydroErosionSimulateComponent::UHydroErosionSimulateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHydroErosionSimulateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHydroErosionSimulateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


/************************Shaders**************************/
class FInitSimuDataCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FInitSimuDataCS)
	SHADER_USE_PARAMETER_STRUCT(FInitSimuDataCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructureBuffer<float> , WaterHeightBuffer)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float> , SedimentBuffer)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FVector4> , OutFluxBuffer)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FVector2f>, VelocityBuffr)
	END_SHADER_PARAMETER_STRUCT()
	
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return RHISupportsComputeShaders(Parameters.Platform);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//OutEnvironment.SetDefine();
	}

};
IMPLEMENT_GLOBAL_SHADER(FInitSimuDataCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"InitSimuDataCS" , SF_Compute);

class FIncreaseWaterCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FIncreaseWaterCS)
	SHADER_USE_PARAMETER_STRUCT(FIncreaseWaterCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(float ,TexSize)
		SHADER_PARAMETER(float ,RainAmount)
		SHADER_PARAMETER(FVector2D , WaterCenter)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float> , WaterHeightW)
	END_SHADER_PARAMETER_STRUCT()
	
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return RHISupportsComputeShaders(Parameters.Platform);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		//OutEnvironment.SetDefine();
	}

};
IMPLEMENT_GLOBAL_SHADER(FIncreaseWaterCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"IncreaseWaterCS" , SF_Compute);

/************************Shaders**************************/

void UHydroErosionSimulateComponent::InitSimuData_RenderThread(UTextureRenderTarget2D* InRenderTarget)
{
	check(IsInGameThread());

	//拉起渲染线程
	ENQUEUE_RENDER_COMMAND(HydroErosionSimulate)
	(
	[& ,this, InRenderTarget](FRHICommandListImmediate &RHICmdList)
	{
		FRDGBuilder GraphBuilder(RHICmdList);

		uint32 BufferElement = InRenderTarget->SizeX * InRenderTarget->SizeY; 
		FRDGTextureDesc TextureDesc ( FRDGTextureDesc::Create2D (
					FIntPoint(InRenderTarget->SizeX,InRenderTarget->SizeY),
					EPixelFormat::PF_R8G8B8A8,
					FClearValueBinding::None,
					TexCreate_UAV | TexCreate_ShaderResource | TexCreate_NoFastClear));
		//初始化Buffer,Texture
		//FRDGTextureRef TerrainHeight_Texture = GraphBuilder.CreateTexture(TextureDesc , TEXT("Terrain_Height_Texture"));
		FRDGBufferRef WaterHeight_Buffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float) ,BufferElement) , TEXT("Water_Height_Buffer") ,ERDGBufferFlags::MultiFrame);
		FRDGBufferRef Sediment_Buffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float) ,BufferElement) , TEXT("Sediment_Buffer") ,ERDGBufferFlags::MultiFrame);
		FRDGBufferRef OutFlux_Buffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float)*4 ,BufferElement) , TEXT("OutFlux_Buffer") ,ERDGBufferFlags::MultiFrame);
		FRDGBufferRef Velocity_Buffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float)*2 ,BufferElement) , TEXT("Velocity_Buffer") ,ERDGBufferFlags::MultiFrame);

		
		const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);

		const FIntVector GroupSize = FComputeShaderUtils::GetGroupCount( FIntPoint(InRenderTarget->SizeX ,InRenderTarget->SizeY) , ThreadSize );
		
		//Init Pass
		{
			typedef FInitSimuDataCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
			
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->WaterHeightBuffer = GraphBuilder.CreateUAV(WaterHeight_Buffer);
			PassParameters->SedimentBuffer = GraphBuilder.CreateUAV(Sediment_Buffer);
			PassParameters->OutFluxBuffer = GraphBuilder.CreateUAV(OutFlux_Buffer);
			PassParameters->VelocityBuffr = GraphBuilder.CreateUAV(Velocity_Buffer);
			

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Init_Simu_Data_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}
		
		//转换外部存储
		ConvertToExternalBuffer(GraphBuilder , WaterHeight_Buffer , PooledBuffer_WaterHeight);
		ConvertToExternalBuffer(GraphBuilder , Sediment_Buffer , PooledBuffer_Sediment);
		ConvertToExternalBuffer(GraphBuilder , OutFlux_Buffer ,PooledBuffer_OutFlux);
		ConvertToExternalBuffer(GraphBuilder , Velocity_Buffer ,PoolBuffer_Velocity);
		
		//ConvertToExternalTexture(GraphBuilder,TerrainHeight_Texture , HydroErosionSimData::PooledRenderTarget_TerrainHeight);

		//修改数据 LockBufferData
		
		/*float* WaterHeightBuffer_Data = (float*)GraphBuilder.RHICmdList.LockStructuredBuffer(WaterHeight_Buffer->GetRHIStructuredBuffer() ,0 ,sizeof(float) ,EResourceLockMode::RLM_WriteOnly);
		*WaterHeightBuffer_Data = float(0.0);
		float* Sediment_Buffer_Data = (float*)GraphBuilder.RHICmdList.LockStructuredBuffer(Sediment_Buffer->GetRHIStructuredBuffer() ,0 ,sizeof(float) ,EResourceLockMode::RLM_WriteOnly);
		*Sediment_Buffer_Data = float(0.0);
		FVector4* OutFlux_Buffer_Data = (FVector4*)GraphBuilder.RHICmdList.LockStructuredBuffer(OutFlux_Buffer->GetRHIStructuredBuffer() ,0 ,sizeof(float)*4 ,EResourceLockMode::RLM_WriteOnly);
		*OutFlux_Buffer_Data = FVector4(0.0);
		FVector2D* Velocity_Buffer_Data = (FVector2D*)GraphBuilder.RHICmdList.LockStructuredBuffer(Velocity_Buffer->GetRHIStructuredBuffer() ,0 ,sizeof(float)*2 ,EResourceLockMode::RLM_WriteOnly);
		*Velocity_Buffer_Data = FVector2D(0.0);

		//UnlockBuffer 给GPU计算
		GraphBuilder.RHICmdList.UnlockStructuredBuffer(WaterHeight_Buffer->GetRHIStructuredBuffer());
		GraphBuilder.RHICmdList.UnlockStructuredBuffer(Sediment_Buffer->GetRHIStructuredBuffer());
		GraphBuilder.RHICmdList.UnlockStructuredBuffer(OutFlux_Buffer->GetRHIStructuredBuffer());
		GraphBuilder.RHICmdList.UnlockStructuredBuffer(Velocity_Buffer->GetRHIStructuredBuffer());*/

		GraphBuilder.Execute();
	});
	bHasInitBufferData = true;
	UE_LOG(LogTemp , Warning ,TEXT("Simulate Data Has Prepeared!!!"));
	uint32 Test = PooledBuffer_WaterHeight->Desc.BytesPerElement;
}

void UHydroErosionSimulateComponent::SimulateHydroErosion_RenderThread(UTextureRenderTarget2D* InRenderTarget , FVector WaterData)
{
	check(IsInGameThread());

	UE_LOG(LogTemp , Warning , TEXT("Current Buffer Initialize : %s") ,  bHasInitBufferData ? TEXT("True") : TEXT("False"));
	if(bHasInitBufferData == false)
	{
		InitSimuData_RenderThread(InRenderTarget);
		return;
	}

	//拉起渲染线程
	ENQUEUE_RENDER_COMMAND(HydroErosionSimulate)
	(
	[ &, InRenderTarget](FRHICommandListImmediate &RHICmdList)
	{
		FRDGBuilder GraphBuilder(RHICmdList);

		uint32 BufferElement = InRenderTarget->SizeX * InRenderTarget->SizeY; 
		FRDGTextureDesc TextureDesc ( FRDGTextureDesc::Create2D (
					FIntPoint(InRenderTarget->SizeX,InRenderTarget->SizeY),
					EPixelFormat::PF_R8G8B8A8,
					FClearValueBinding::None,
					TexCreate_UAV | TexCreate_ShaderResource | TexCreate_NoFastClear));

		FRDGBufferRef WaterHeight_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_WaterHeight);
		FRDGBufferRef Sediment_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_Sediment);
		FRDGBufferRef OutFlux_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_OutFlux);
		FRDGBufferRef Velocity_Buffer= GraphBuilder.RegisterExternalBuffer(PoolBuffer_Velocity);

		//Global Shader Map  & Dispatch GroupSize
			const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
			FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
			const FIntVector GroupSize = FComputeShaderUtils::GetGroupCount( FIntPoint(InRenderTarget->SizeX , InRenderTarget->SizeY) , ThreadSize );

		//IncreaseWater Pass
		{
			typedef FIncreaseWaterCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
			
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->WaterHeightW = GraphBuilder.CreateUAV(WaterHeight_Buffer);
			PassParameters->TexSize = InRenderTarget->SizeX;
			PassParameters->WaterCenter = FVector2D(WaterData.X , WaterData.Y);
			PassParameters->RainAmount = WaterData.Z;

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Advection_CS_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
			UE_LOG(LogTemp ,Warning , TEXT("Increase Water Pass Done! And Buffer Element is %i") , (int)WaterHeight_Buffer->Desc.NumElements);
		}

		GraphBuilder.Execute();
	});
}

