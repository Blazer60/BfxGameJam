// Fill out your copyright notice in the Description page of Project Settings.


#include "RewindCallback.h"

#include "GenericPlatform/GenericPlatformChunkInstall.h"


URewindCallback::URewindCallback()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URewindCallback::Broadcast(bool bIsTriggered, bool bIsStarted, bool bIsCompleted, float Delta)
{
	Broadcast_Impl(bIsTriggered, bIsStarted, bIsCompleted, Delta);
}

int URewindCallback::Subscribe(const FOnRewindSignature& Callback)
{
	const auto Lambda = [=](bool bIsTriggered, bool bIsStarted, bool bIsCompleted, float Delta)
	{
		Callback.ExecuteIfBound(bIsTriggered, bIsStarted, bIsCompleted, Delta);
	};
	return Subscribe_Impl(std::move(Lambda));
}

void URewindCallback::Unsubscribe(const int Token)
{
	Unsubscribe_Impl(Token);
}

