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

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicHandle();
// Set Traget Location for grabbed object
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}
	void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
// if has sweep result then ->		
	if (HasHit)
	{
// kick rigid body to wake up		
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");
// grab component at location
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation());
	}
}

// Release method
	void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicHandle();
		if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
		{
			AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
			GrabbedActor->Tags.Remove("Grabbed");
			PhysicsHandle->ReleaseComponent();
		}
}

// Get PhysicHandle method 
	UPhysicsHandleComponent* UGrabber::GetPhysicHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
		if (Result == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Grabber rewuired PhysicsHaldeComponent!"));
		}
	return Result;
}

	bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
	{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
// create collision shape with radius
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

// create hit result from Sweeping
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);
	}
