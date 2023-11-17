// Fill out your copyright notice in the Description page of Project Settings.


#include "RewindComponent.h"
#include "../Common/Common.h"
#include "GameFramework/CharacterMovementComponent.h"


URewindComponent::URewindComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URewindComponent::BeginPlay()
{
	Super::BeginPlay();
	Print("Starting Rewind Component.");
}

void URewindComponent::TrackPath(const float DeltaTime)
{
	Timer += DeltaTime;
	if (Timer > UpdateRate)
	{
		Timer -= UpdateRate;
		const AActor* Owner = GetOwner();
		const FVector Location = Owner->GetActorLocation();
		const FVector Velocity = Owner->GetVelocity();

		RewindData.Emplace(FRewindData { Location, Velocity });

		if (RewindData.Num() > MaximumCount)
			RewindData.RemoveAt(0);
	}
}


void URewindComponent::TickComponent(
	const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTrackPath)
		TrackPath(DeltaTime);
}

void URewindComponent::RewindThroughPath(const float Delta)
{
	const int32 Index = FMath::Max(RewindData.Num() - ceil(Delta / UpdateRate), 0);
	const float Alpha = (Delta / UpdateRate) - floor(Delta / UpdateRate);
	const auto DataA = RewindData[Index];
	const auto DataB = RewindData[FMath::Max(Index - 1, 0)];
	GetOwner()->SetActorLocation(FMath::Lerp(DataA.Position, DataB.Position, Alpha));
}

void URewindComponent::FinishRewindThroughPath(const float Delta)
{
	const int32 Index = FMath::Max(RewindData.Num() - ceil(Delta / UpdateRate), 0);
	const float Alpha = (Delta / UpdateRate) - floor(Delta / UpdateRate);
	const auto [PositionA, VelocityA] = RewindData[Index];
	const auto [PositionB, VelocityB] = RewindData[FMath::Max(Index - 1, 0)];
	
	GetOwner()->SetActorLocation(FMath::Lerp(PositionA, PositionB, Alpha));
	const auto CharacterMovementComponent = GetOwner()->GetComponentByClass<UCharacterMovementComponent>();
	CharacterMovementComponent->Velocity = FMath::Lerp(VelocityA, VelocityB, Alpha);
	
	const int32 Count = RewindData.Num() - Index;
	RewindData.RemoveAt(Index, Count);
}

