// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	bWantsBeginPlay = true;

	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::BeginPlay()
{
	if (!GetOwner()) { return; }
	TankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	return;
}

void UTankTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// Calculate sidewasys slip speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work-out required deceleration to correct 
	auto CounterAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();
	// Calculate and apply sideways force
	auto CounterForce = (TankRootMesh->GetMass() * CounterAcceleration) / 2; //because there's 2 tracks
	TankRootMesh->AddForce(CounterForce);
	return;
}

void UTankTracks::SetThrottle(float Throttle) 
{
	
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	return;
}

