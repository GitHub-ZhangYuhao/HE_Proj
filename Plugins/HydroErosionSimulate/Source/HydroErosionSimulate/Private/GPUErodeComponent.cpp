// Fill out your copyright notice in the Description page of Project Settings.


#include "GPUErodeComponent.h"
#include "GPUEdosionShaders.h"
#include "RenderGraph.h"
#include "Engine/TextureRenderTarget2D.h"

// Sets default values for this component's properties
UGPUErodeComponent::UGPUErodeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGPUErodeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGPUErodeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGPUErodeComponent::InvokeGPUInitData_RenderThread(UTextureRenderTarget2D* InRenderTarget)
{
	
	FTexture2DRHIRef In_RenderTargetRHI_Result = InRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	
		//拉起渲染线程
	ENQUEUE_RENDER_COMMAND(HydroErosionSimulate)
	(
	[& ,this,In_RenderTargetRHI_Result, InRenderTarget](FRHICommandListImmediate &RHICmdList)
	{
		if(bIsInit == true)
		{
			PooledBuffer_Flux.SafeRelease();
			PooledBuffer_Velocity.SafeRelease();
		}
		
		FRDGBuilder GraphBuilder(RHICmdList);

		uint32 BufferElement = InRenderTarget->SizeX * InRenderTarget->SizeY; 
		FRDGTextureDesc TextureDesc ( FRDGTextureDesc::Create2D (
					FIntPoint(InRenderTarget->SizeX,InRenderTarget->SizeY),
					InRenderTarget->GetFormat(),
					FClearValueBinding::None,
					TexCreate_UAV | TexCreate_ShaderResource | TexCreate_NoFastClear));
		//初始化Buffer,Texture
		FRDGBufferRef Velocity_Buffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float)*2 ,BufferElement) , TEXT("Velocity_Buffer") ,ERDGBufferFlags::MultiFrame);
		FRDGBufferRef Flux_Buffer = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float)*4 ,BufferElement) , TEXT("Flux_Buffer") ,ERDGBufferFlags::MultiFrame);
		FRDGTextureRef SimulateTex = GraphBuilder.CreateTexture(TextureDesc ,TEXT("SimulateTex"));
		
		const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);

		const FIntVector GroupSize = FComputeShaderUtils::GetGroupCount( FIntPoint(InRenderTarget->SizeX ,InRenderTarget->SizeY) , ThreadSize );
		
		//Init Pass
		{
			typedef FInitSimuData SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
			
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->InHeightMapTex=In_RenderTargetRHI_Result;
			PassParameters->InHeightMapTexSampler = TStaticSamplerState<SF_Bilinear ,AM_Clamp ,AM_Clamp ,AM_Clamp ,0>::GetRHI();
			PassParameters->FluxW = GraphBuilder.CreateUAV(Flux_Buffer);
			PassParameters->VelocityW = GraphBuilder.CreateUAV(Velocity_Buffer);
			PassParameters->SimulateTexW = GraphBuilder.CreateUAV(SimulateTex);
			

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Init_Simu_Data_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}
		TRefCountPtr<IPooledRenderTarget> Pooled_SimulateTexture = nullptr;
		GraphBuilder.QueueTextureExtraction(SimulateTex ,&Pooled_SimulateTexture);

		//转换外部存储
		ConvertToExternalBuffer(GraphBuilder, Flux_Buffer, PooledBuffer_Flux);
		ConvertToExternalBuffer(GraphBuilder, Velocity_Buffer , PooledBuffer_Velocity);
		// ConvertToExternalTexture(GraphBuilder,SimulateTex,Pooled_SimulateTexture);
		GraphBuilder.Execute();
		
		RHICmdList.CopyTexture(Pooled_SimulateTexture->GetRenderTargetItem().ShaderResourceTexture,In_RenderTargetRHI_Result->GetTexture2D(),FRHICopyTextureInfo());
	});
	
	bIsInit = true;
	UE_LOG(LogTemp , Warning ,TEXT("Simulate Data Has Prepeared!!!"));
}

void UGPUErodeComponent::InvokeGPUErosion_RenderThread(UTextureRenderTarget2D* InRenderTarget)
{
	check(IsInGameThread());
	FTexture2DRHIRef In_RenderTargetRHI_Result = InRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();

	if (bIsInit != true)
	{
		InvokeGPUInitData_RenderThread(InRenderTarget);
	}
		//拉起渲染线程
	ENQUEUE_RENDER_COMMAND(HydroErosionSimulate)
	(
	[& ,this,In_RenderTargetRHI_Result, InRenderTarget](FRHICommandListImmediate &RHICmdList)
	{
		FRDGBuilder GraphBuilder(RHICmdList);

		uint32 BufferElement = InRenderTarget->SizeX * InRenderTarget->SizeY; 
		FRDGTextureDesc TextureDesc ( FRDGTextureDesc::Create2D (
					FIntPoint(InRenderTarget->SizeX,InRenderTarget->SizeY),
					InRenderTarget->GetFormat(),
					FClearValueBinding::None,
					TexCreate_UAV | TexCreate_ShaderResource | TexCreate_NoFastClear));
		//Load Buffer,Init Texture
		FRDGBufferRef Velocity_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_Velocity);
		FRDGBufferRef Flux_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_Flux);
		FRDGTextureRef SimulateTex = GraphBuilder.CreateTexture(TextureDesc ,TEXT("SimulateTex"));
		
		const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
		const FIntVector GroupSize = FComputeShaderUtils::GetGroupCount( FIntPoint(InRenderTarget->SizeX ,InRenderTarget->SizeY) , ThreadSize );
		
		//Add Height Water Pass
		{
			typedef FUpdateWaterAndHeightCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
			
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->RainData = RainData;
			PassParameters->SimulateTexR = In_RenderTargetRHI_Result;
			PassParameters->SimulateTexSampler = TStaticSamplerState<SF_Bilinear ,AM_Clamp ,AM_Clamp ,AM_Clamp ,0>::GetRHI();
			PassParameters->SimulateTexW = GraphBuilder.CreateUAV(SimulateTex);
			
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Update_Height_Water_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}

		//拷贝到RT
		TRefCountPtr<IPooledRenderTarget> Pooled_SimulateTexture = nullptr;
		GraphBuilder.QueueTextureExtraction(SimulateTex ,&Pooled_SimulateTexture);

		//转换外部存储
		ConvertToExternalBuffer(GraphBuilder, Flux_Buffer, PooledBuffer_Flux);
		ConvertToExternalBuffer(GraphBuilder, Velocity_Buffer , PooledBuffer_Velocity);
		// ConvertToExternalTexture(GraphBuilder,SimulateTex,Pooled_SimulateTexture);
		GraphBuilder.Execute();
		
		RHICmdList.CopyTexture(Pooled_SimulateTexture->GetRenderTargetItem().ShaderResourceTexture,In_RenderTargetRHI_Result->GetTexture2D(),FRHICopyTextureInfo());

		SimulationTimes++;
		UE_LOG(LogTemp , Warning ,TEXT("Simulation Times : %i") , SimulationTimes);
	});
}

