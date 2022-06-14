// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RenderGraphResources.h"
#include "HydroErosionSimulateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYDROEROSIONSIMULATE_API UHydroErosionSimulateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHydroErosionSimulateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	Terrain Height	: B
	Water Height	: D
	Sediment		: S
	OutFlux			: F
	VelocityVec		: V
	*/
	UPROPERTY(BlueprintReadWrite)
	int ThreadSize = 32;

	bool bHasInitBufferData = false;
	//TRefCountPtr<IPooledRenderTarget> PooledRenderTarget_TerrainHeight;	//地形高度 :float
	TRefCountPtr<FRDGPooledBuffer> PooledBuffer_WaterHeight;	//水面高度 :float
	TRefCountPtr<FRDGPooledBuffer> PooledBuffer_Sediment;	//悬浮泥沙量 :float
	TRefCountPtr<FRDGPooledBuffer> PooledBuffer_OutFlux;		//流出通量	:float4 (Fl,Fr,Ft,Fb)
	TRefCountPtr<FRDGPooledBuffer> PoolBuffer_Velocity;		//速度矢量	:float2 (u,v)

	UFUNCTION(BlueprintCallable , Category = "HydroSimu")
	void InitSimuData_RenderThread(UTextureRenderTarget2D* InRenderTarget);

	UFUNCTION(BlueprintCallable , Category = "HydroSimu")
	void SimulateHydroErosion_RenderThread(UTextureRenderTarget2D* InRenderTarget ,FVector WaterData);
};
