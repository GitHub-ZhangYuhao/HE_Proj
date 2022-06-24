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

void UGPUErodeComponent::InvokeGPUErosion_RenderThread(UTextureRenderTarget2D* InRenderTarget ,UTextureRenderTarget2D* DebugRenderTarget)
{
	check(IsInGameThread());
	FTexture2DRHIRef In_RenderTargetRHI_Result = InRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	FTexture2DRHIRef Debug_RenderTargetRHI_Result = DebugRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	
	if (bIsInit != true)
	{
		InvokeGPUInitData_RenderThread(InRenderTarget);
	}
		//拉起渲染线程
	ENQUEUE_RENDER_COMMAND(HydroErosionSimulate)
	(
	[& ,this,In_RenderTargetRHI_Result, InRenderTarget ,Debug_RenderTargetRHI_Result ,DebugRenderTarget](FRHICommandListImmediate &RHICmdList)
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
		FRDGBufferRef Flux_Buffer_1 = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float)*4 ,BufferElement) , TEXT("Flux_Buffer_1") ,ERDGBufferFlags::MultiFrame);
		FRDGTextureRef SimulateTex = GraphBuilder.CreateTexture(TextureDesc ,TEXT("SimulateTex"));
		//For Swap Tex
		FRDGTextureRef SimulateTex_1 = GraphBuilder.CreateTexture(TextureDesc ,TEXT("SimulateTex_1"));
		FRDGTextureRef DebugTex = GraphBuilder.CreateTexture(TextureDesc ,TEXT("DebugTex"));
		
		
		const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
		const FIntVector GroupSize = FComputeShaderUtils::GetGroupCount( FIntPoint(InRenderTarget->SizeX ,InRenderTarget->SizeY) , ThreadSize );
		
		//Add Height Water Pass
		//	In : Tex(height ,water ,sediment ,hardness)
		//	Out: Tex(height ,water ,sediment ,hardness)
		{
			typedef FUpdateWaterAndHeightCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
			
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->HeightAmount = HeightAount;
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
		//Flux Pass
		// In : Tex(height ,water ,sediment ,hardness)
		// Out: Flux
		{
			typedef FOutFluxComputeCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
						
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->SimulateTexR = In_RenderTargetRHI_Result;
			PassParameters->SimulateTexSampler = TStaticSamplerState<SF_Bilinear ,AM_Clamp ,AM_Clamp ,AM_Clamp ,0>::GetRHI();
			PassParameters->FluxR = GraphBuilder.CreateSRV(Flux_Buffer);
			PassParameters->FluxW = GraphBuilder.CreateUAV(Flux_Buffer_1);
			PassParameters->DebugTex = GraphBuilder.CreateUAV(DebugTex);
			
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("OutFlux_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}
		
		
		//Velocity Pass
		{
			typedef FVelocityComputeCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
								
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->WaterVelocitySwap = WaterVelocitySwap;
			PassParameters->SimulateTexR = SimulateTex;
			PassParameters->SimulateTexSampler = TStaticSamplerState<SF_Bilinear ,AM_Clamp ,AM_Clamp ,AM_Clamp ,0>::GetRHI();
			PassParameters->FluxR = GraphBuilder.CreateSRV(Flux_Buffer_1);
			PassParameters->VelocityW = GraphBuilder.CreateUAV(Velocity_Buffer);
			
			PassParameters->SimulateTexW = GraphBuilder.CreateUAV(SimulateTex_1);
			PassParameters->DebugTex = GraphBuilder.CreateUAV(DebugTex);
					
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Velocityes_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}
		//ErodSion Pass
		{
			typedef FHydroErosionCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
								
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->SimulateTexR = SimulateTex_1;
			PassParameters->SimulateTexSampler = TStaticSamplerState<SF_Bilinear ,AM_Clamp ,AM_Clamp ,AM_Clamp ,0>::GetRHI();
			PassParameters->VelocityR = GraphBuilder.CreateSRV(Velocity_Buffer);
			PassParameters->SimulateTexW = GraphBuilder.CreateUAV(SimulateTex);
			PassParameters->DebugTex = GraphBuilder.CreateUAV(DebugTex);
					
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("HydroErode_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}
		{
			typedef FSedimentAdvectionCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
								
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->SimulateTexR = SimulateTex;
			PassParameters->SimulateTexSampler = TStaticSamplerState<SF_Trilinear ,AM_Clamp ,AM_Clamp ,AM_Clamp ,0>::GetRHI();
			PassParameters->VelocityR = GraphBuilder.CreateSRV(Velocity_Buffer);
			PassParameters->SimulateTexW = GraphBuilder.CreateUAV(SimulateTex_1);
			PassParameters->DebugTex = GraphBuilder.CreateUAV(DebugTex);
					
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Sediment_Advect_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
		}

		//拷贝到RT
		TRefCountPtr<IPooledRenderTarget> Pooled_SimulateTexture = nullptr;
		GraphBuilder.QueueTextureExtraction(SimulateTex_1 ,&Pooled_SimulateTexture);
		//Debug
		TRefCountPtr<IPooledRenderTarget> Pooled_DebugTexture = nullptr;
		GraphBuilder.QueueTextureExtraction(DebugTex ,&Pooled_DebugTexture);

		//转换外部存储
		ConvertToExternalBuffer(GraphBuilder, Flux_Buffer_1, PooledBuffer_Flux);
		ConvertToExternalBuffer(GraphBuilder, Velocity_Buffer , PooledBuffer_Velocity);
		// ConvertToExternalTexture(GraphBuilder,SimulateTex,Pooled_SimulateTexture);
		GraphBuilder.Execute();
		
		RHICmdList.CopyTexture(Pooled_SimulateTexture->GetRenderTargetItem().ShaderResourceTexture,In_RenderTargetRHI_Result->GetTexture2D(),FRHICopyTextureInfo());

		//Debug
		RHICmdList.CopyTexture(Pooled_DebugTexture->GetRenderTargetItem().ShaderResourceTexture ,Debug_RenderTargetRHI_Result->GetTexture2D(),FRHICopyTextureInfo());
		
		SimulationTimes++;
		UE_LOG(LogTemp , Warning ,TEXT("Simulation Times : %i") , SimulationTimes);
	});
}

