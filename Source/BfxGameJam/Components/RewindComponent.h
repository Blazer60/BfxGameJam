// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BfxGameJam/Common/RewindData.h"
#include "Components/ActorComponent.h"
#include "RewindComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BFXGAMEJAM_API URewindComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URewindComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void RewindThroughPath(float Delta);

	UFUNCTION(BlueprintCallable)
	void FinishRewindThroughPath(const float Delta);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTrackPath { true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpdateRate { 0.1f };
	
	TArray<FRewindData> RewindData;
protected:
	virtual void BeginPlay() override;
	void TrackPath(const float DeltaTime);

	int32 MaximumCount { 1000 };
	float Timer { 0.f };

	float GlobalTimer { 0.f };
};
