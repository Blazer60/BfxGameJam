// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Callback.h"
#include "RewindCallback.generated.h"

class UItemOwner;

DECLARE_DYNAMIC_DELEGATE_FourParams(FOnRewindSignature, bool, bIsTriggered, bool, bIsStarted, bool, bIsCompleted, float, Delta);

UCLASS(ClassGroup=(Callback), meta=(BlueprintSpawnableComponent))
class BFXGAMEJAM_API URewindCallback
	: public UActorComponent, public TCallback<bool, bool, bool, float>
{
	GENERATED_BODY()
public:
	URewindCallback();

	UFUNCTION(BlueprintCallable)
	void Broadcast(bool bIsTriggered, bool bIsStarted, bool bIsCompleted, float Delta);

	UFUNCTION(BlueprintCallable)
	int Subscribe(const FOnRewindSignature &Callback);
	
	UFUNCTION(BlueprintCallable)
	void Unsubscribe(int Token);
};
