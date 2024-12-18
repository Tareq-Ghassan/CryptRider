// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetCurrentLocation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector TargetLocation = OriginalLocation;
	if (ShouldMove) 
	{
		TargetLocation = GetTargetLocation();
	}
	FVector NewLocation = FMath::VInterpConstantTo(
		GetCurrentLocation(),
		TargetLocation,
		DeltaTime,
		GetSpeed()
	);
	GetOwner()->SetActorLocation(NewLocation);
}

float UMover::GetSpeed() {
	return MoveOffset.Length() / MoveTime;
}

FVector UMover::GetCurrentLocation() {
	return GetOwner()->GetActorLocation();
}

FVector UMover::GetTargetLocation() {

	return OriginalLocation + MoveOffset;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}
