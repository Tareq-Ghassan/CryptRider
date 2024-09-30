// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("name: %s"), *PhysicsHandle->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Null pointer Exception, please check if you hooked up Physics Handle Componant Grabber"));

	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GraberRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	AActor* HitActor = HitResult.GetActor();

	if (HasHit) {
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *HitActor->GetActorNameOrLabel());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Actor hit"));

	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Display, TEXT("Releas grabber"));
}

