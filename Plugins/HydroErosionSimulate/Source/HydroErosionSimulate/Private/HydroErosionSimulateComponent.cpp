// Fill out your copyright notice in the Description page of Project Settings.


#include "HydroErosionSimulateComponent.h"

#include "RenderGraphUtils.h"
#include "AVEncoder/Private/Microsoft/Windows/ThirdParty/AmdAmf/core/Compute.h"
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
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructureBuffer<float> , HeightBuffer)
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

class FUpdateHightCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FUpdateHightCS)
	SHADER_USE_PARAMETER_STRUCT(FUpdateHightCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float> , HeightBufferR)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float> ,HeightBufferW)
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
IMPLEMENT_GLOBAL_SHADER(FUpdateHightCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"UpdateHeightTextureCS" , SF_Compute);

class FIncreaseWaterCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FIncreaseWaterCS)
	SHADER_USE_PARAMETER_STRUCT(FIncreaseWaterCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(float ,TexSize)
		SHADER_PARAMETER(float ,RainAmount)
		SHADER_PARAMETER(FVector2D , WaterCenter)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FVector4> , WaterHeightW)
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float> , WaterHeightR)
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

class FOutFluxCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FOutFluxCS)
	SHADER_USE_PARAMETER_STRUCT(FOutFluxCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float> ,HeightBufferR)				//b t	(R channel)
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float> ,WaterBufferR)		//d 1
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<FVector4> ,OutFluxBufferR)	//F t
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructureBuffer<FVector4> , OutFluxBufferW)	//F Δt+t
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
IMPLEMENT_GLOBAL_SHADER(FOutFluxCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"OutFluxCS" , SF_Compute);

class FWaterSurfaceVelocityFieldCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FWaterSurfaceVelocityFieldCS)
	SHADER_USE_PARAMETER_STRUCT(FWaterSurfaceVelocityFieldCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<FVector4> , OutFluxBufferR)
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float> , WaterBufferR)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructureBuffer<float> , WaterBufferW)
		SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructureBuffer<FVector2f> , VelocityBuffrW)
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
IMPLEMENT_GLOBAL_SHADER(FWaterSurfaceVelocityFieldCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"UpdateWaterSurfaceAndVelocityFieldCS" , SF_Compute);

class FErosionDepositionCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FErosionDepositionCS)
	SHADER_USE_PARAMETER_STRUCT(FErosionDepositionCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )

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
IMPLEMENT_GLOBAL_SHADER(FErosionDepositionCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"ErosionDepositionCS" , SF_Compute);


class FDebugVisualizeCS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FDebugVisualizeCS)
	SHADER_USE_PARAMETER_STRUCT(FDebugVisualizeCS , FGlobalShader)

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<FVector2> , InFloat2Buffer)
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float> , InFloatBuffer)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4> , OutTexture)
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
IMPLEMENT_GLOBAL_SHADER(FDebugVisualizeCS ,"/Plugins/HydroErosionSimulate/Shaders/Private/HydroErosionSimu.usf" ,"DebugVisulizeCS" , SF_Compute);
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
		FRDGBufferRef Height_Buffer =  GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float) ,BufferElement) , TEXT("Height_Buffer") ,ERDGBufferFlags::MultiFrame);
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
			PassParameters->HeightBuffer = GraphBuilder.CreateUAV(Height_Buffer);
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
		ConvertToExternalBuffer(GraphBuilder , Height_Buffer , PoolBuffer_Height);
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

void UHydroErosionSimulateComponent::SimulateHydroErosion_RenderThread(UTextureRenderTarget2D* InRenderTarget ,UTextureRenderTarget2D* DebugRenderTarget  , FVector WaterData)
{
	check(IsInGameThread());
	
	//Debug RT
	FTexture2DRHIRef In_RenderTargetRHI_Result = InRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	FTexture2DRHIRef Debug_RenderTargetRHI_Result = DebugRenderTarget->GameThread_GetRenderTargetResource()->GetRenderTargetTexture();
	
	// Buffer Data Init
	UE_LOG(LogTemp , Warning , TEXT("Current Buffer Initialize : %s") ,  bHasInitBufferData ? TEXT("True") : TEXT("False"));
	// 如果资源没有初始化，初始化资源
	if(bHasInitBufferData == false)
	{
		InitSimuData_RenderThread(InRenderTarget);
		return;
	}
	
	
	//拉起渲染线程
	ENQUEUE_RENDER_COMMAND(HydroErosionSimulate)
	(
	[ &, InRenderTarget ,In_RenderTargetRHI_Result , Debug_RenderTargetRHI_Result](FRHICommandListImmediate &RHICmdList)
	{
		FRDGBuilder GraphBuilder(RHICmdList);

		uint32 BufferElement = InRenderTarget->SizeX * InRenderTarget->SizeY; 
		FRDGTextureDesc TextureDesc ( FRDGTextureDesc::Create2D (
					FIntPoint(InRenderTarget->SizeX,InRenderTarget->SizeY),
					In_RenderTargetRHI_Result->GetFormat(),
					FClearValueBinding::None,
					TexCreate_UAV | TexCreate_ShaderResource | TexCreate_NoFastClear));

		//HeightTexteure
		//FRDGTextureRef HeightTexture = GraphBuilder.CreateTexture(TextureDesc ,TEXT("TerrainHeightTexture") );
		//BufferData

		FRDGBufferRef Height_Buffer = GraphBuilder.RegisterExternalBuffer(PoolBuffer_Height);
		
		FRDGBufferRef WaterHeight_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_WaterHeight);
		FRDGBufferRef WaterHeight_Buffer_d1 =  GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float) ,BufferElement) , TEXT("Water_Height_Buffer_d1") ,ERDGBufferFlags::MultiFrame);
		//FRDGBufferRef WaterHeight_Buffer_d2 =  GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float) ,BufferElement) , TEXT("Water_Height_Buffer_d2") ,ERDGBufferFlags::MultiFrame);
		FRDGBufferRef Sediment_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_Sediment);
		FRDGBufferRef OutFlux_Buffer = GraphBuilder.RegisterExternalBuffer(PooledBuffer_OutFlux);
		FRDGBufferRef Velocity_Buffer= GraphBuilder.RegisterExternalBuffer(PoolBuffer_Velocity);


		//Debug
		{
			UE_LOG(LogTemp ,Warning , TEXT("Increase Water Pass Buffer Element is %i") , (int)WaterHeight_Buffer->Desc.NumElements);
			UE_LOG(LogTemp ,Warning , TEXT("OutFlux_Buffer Element is %i") , (int)OutFlux_Buffer->Desc.NumElements);
			//UE_LOG(LogTemp ,Warning , TEXT("Increase Water Pass Buffer Element is %i") , (int)WaterHeight_Buffer->Desc.NumElements);
			//UE_LOG(LogTemp ,Warning , TEXT("Increase Water Pass Buffer Element is %i") , (int)WaterHeight_Buffer->Desc.NumElements);
		}
		
		
		//Global Shader Map  & Dispatch GroupSize
			const ERHIFeatureLevel::Type FeatureLevel = GMaxRHIFeatureLevel;
			FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
			const FIntVector GroupSize = FComputeShaderUtils::GetGroupCount( FIntPoint(InRenderTarget->SizeX , InRenderTarget->SizeY) , ThreadSize );


		//Update Pass
		{
			FRDGBufferRef Height_Buffer_d1 =  GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float) ,BufferElement) , TEXT("Height_Buffer_d1") ,ERDGBufferFlags::MultiFrame);
			
			typedef FUpdateHightCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
					
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->HeightBufferR = GraphBuilder.CreateSRV(Height_Buffer);
			PassParameters->HeightBufferW = GraphBuilder.CreateUAV(Height_Buffer_d1);

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("IncreaseWater_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
			UE_LOG(LogTemp ,Warning , TEXT("Update Height Texture Pass Done!!!"));

			Height_Buffer = Height_Buffer_d1;
		}
		
		//IncreaseWater Pass
		{
			typedef FIncreaseWaterCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
			
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->WaterHeightR = GraphBuilder.CreateSRV(WaterHeight_Buffer);	
			PassParameters->WaterHeightW = GraphBuilder.CreateUAV(WaterHeight_Buffer_d1);
			PassParameters->TexSize = InRenderTarget->SizeX;
			PassParameters->WaterCenter = FVector2D(WaterData.X , WaterData.Y);
			PassParameters->RainAmount = WaterData.Z;

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("IncreaseWater_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
			UE_LOG(LogTemp ,Warning , TEXT("Increase Water Pass Done! And Buffer Element is %i") , (int)WaterHeight_Buffer->Desc.NumElements);
		}

		//OutFlux Pass  Out : F Δt+t (FL , FR , FT , FB)
		{
			FRDGBufferRef TempOutFluxBufferOut = GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float)*4 ,BufferElement) , TEXT("Water_Height_Buffer_d2") ,ERDGBufferFlags::MultiFrame);
			
			typedef FOutFluxCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);

			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->HeightBufferR = GraphBuilder.CreateSRV(Height_Buffer);			//b t
			PassParameters->WaterBufferR = GraphBuilder.CreateSRV(WaterHeight_Buffer_d1);	//d 1
			PassParameters->OutFluxBufferR = GraphBuilder.CreateSRV(OutFlux_Buffer );		//F t
			PassParameters->OutFluxBufferW = GraphBuilder.CreateUAV(TempOutFluxBufferOut);

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("OutFlux_Pass"),
				ComputeShader , PassParameters,
				FIntVector(GroupSize.X , GroupSize.Y , 1));

			OutFlux_Buffer = TempOutFluxBufferOut;		//应该不能用等号赋值
			
			UE_LOG(LogTemp ,Warning , TEXT("OutFlux Pass has been Calculate"));
		}

		//Update WaterBuffer_d2 and Velocity Filed
		{
			typedef FWaterSurfaceVelocityFieldCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
					
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->OutFluxBufferR = GraphBuilder.CreateSRV(OutFlux_Buffer);				//F t+Δt 
			PassParameters->WaterBufferR = GraphBuilder.CreateSRV(WaterHeight_Buffer_d1);		//d1
			PassParameters->WaterBufferW = GraphBuilder.CreateUAV(WaterHeight_Buffer);			//d2
			PassParameters->VelocityBuffrW = GraphBuilder.CreateUAV(Velocity_Buffer);			//V	t+Δt (x,y)

			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("IncreaseWater_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
			
			UE_LOG(LogTemp ,Warning , TEXT("WaterSurfaceVelocityField Pass Is Calculate! "));
		}

		//Debug Pass Resouce
		FRDGTextureDesc DebugTexDesc = FRDGTextureDesc::Create2D(FIntPoint(InRenderTarget->SizeX , InRenderTarget->SizeY) , Debug_RenderTargetRHI_Result->GetFormat() ,FClearValueBinding::Black ,TexCreate_RenderTargetable | TexCreate_ShaderResource | TexCreate_UAV);
		FRDGTextureRef DebugTexture = GraphBuilder.CreateTexture(DebugTexDesc ,TEXT("Debug_Texture"));
		TRefCountPtr<IPooledRenderTarget> Pooled_DebugTexture;
		//Debug Pass
		{
			typedef FDebugVisualizeCS SHADER;
			TShaderMapRef<SHADER> ComputeShader(GlobalShaderMap);
						
						
			SHADER::FParameters* PassParameters = GraphBuilder.AllocParameters<SHADER::FParameters>();
			PassParameters->InFloat2Buffer = GraphBuilder.CreateSRV(Velocity_Buffer);
			PassParameters->InFloatBuffer = GraphBuilder.CreateSRV(WaterHeight_Buffer);
			PassParameters->OutTexture = GraphBuilder.CreateUAV(DebugTexture);
			
			FComputeShaderUtils::AddPass(
				GraphBuilder,
				RDG_EVENT_NAME("Advection_CS_Pass"),
				ComputeShader,PassParameters,
				FIntVector(GroupSize.X,GroupSize.Y,1));
			UE_LOG(LogTemp ,Warning , TEXT("Debug_Pass Is Done"));

			GraphBuilder.QueueTextureExtraction(DebugTexture , &Pooled_DebugTexture);
		}

		GraphBuilder.Execute();

		//Debug
		RHICmdList.CopyTexture(Pooled_DebugTexture->GetRenderTargetItem().ShaderResourceTexture ,Debug_RenderTargetRHI_Result->GetTexture2D() ,FRHICopyTextureInfo());
	});
}

