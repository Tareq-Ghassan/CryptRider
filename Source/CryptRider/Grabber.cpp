// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysiceHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		FVector TargetRotation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetRotation, GetComponentRotation());
	}


}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysiceHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false,5);

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

	if (HasHit) {
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysiceHandle();

	if (PhysicsHandle == nullptr) 
	{
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}
}


 UPhysicsHandleComponent* UGrabber::GetPhysiceHandle() const {
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Null pointer Exception, please check if you hooked up Physics Handle Componant Grabber"));
		return nullptr;
	}
	else 
	{
		return PhysicsHandle;
	}
}
