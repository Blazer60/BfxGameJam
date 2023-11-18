// Fill out your copyright notice in the Description page of Project Settings.


#include "Follower.h"
#include "../Common/Common.h"


// Sets default values for this component's properties
UFollower::UFollower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFollower::BeginPlay()
{
	Super::BeginPlay();

	if (RewindComponent == nullptr)
	{
		Print("No rewind component Set.");
	}
}


// Called every frame
void UFollower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UFollower::MoveThroughTime(const float Delta) const
{
	if (RewindComponent == nullptr)
		return;
	
	TArray<FRewindData> &Data = RewindComponent->RewindData;
	const float Time = (Delta - Data[0].TimeStamp) / RewindComponent->UpdateRate;
	const int32 Index = FMath::Clamp(floor(Time), 0, Data.Num() - 1);
	const int32 Index2 = FMath::Min(Index + 1, Data.Num() - 1);
	const float Alpha = Time - floor(Time);

	GetOwner()->SetActorLocation(FMath::Lerp(Data[Index].Position, Data[Index2].Position, Alpha));
}

