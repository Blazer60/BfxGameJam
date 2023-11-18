// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RewindComponent.h"
#include "Components/ActorComponent.h"
#include "Follower.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BFXGAMEJAM_API UFollower : public UActorComponent
{
	GENERATED_BODY()

public:
	UFollower();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void MoveThroughTime(float Delta) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URewindComponent *RewindComponent;
protected:
	virtual void BeginPlay() override;
};
