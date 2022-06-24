// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RenderGraphResources.h"
#include "Components/ActorComponent.h"
#include "GPUErodeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYDROEROSIONSIMULATE_API UGPUErodeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGPUErodeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int ThreadSize = 32;
	int SimulationTimes = 0;
	bool bIsInit = false;

	//SimulateData
	UPROPERTY(BlueprintReadWrite)
	FVector RainData;
	UPROPERTY(BlueprintReadWrite)
	float HeightAount;

	UPROPERTY(BlueprintReadWrite)
	float WaterVelocitySwap = 1.0f;
	
	TRefCountPtr<FRDGPooledBuffer> PooledBuffer_Flux;
	TRefCountPtr<FRDGPooledBuffer> PooledBuffer_Velocity;

	UFUNCTION(BlueprintCallable , Category = "GPUHydroErosion")
	void InvokeGPUInitData_RenderThread(UTextureRenderTarget2D* InRenderTarget);

	UFUNCTION(BlueprintCallable , Category = "GPUHydroErosion")
	void InvokeGPUErosion_RenderThread(UTextureRenderTarget2D* InRenderTarget ,UTextureRenderTarget2D* DebugRenderTarget);
};
