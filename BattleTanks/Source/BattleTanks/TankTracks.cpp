// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	bWantsBeginPlay = true;

	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::BeginPlay()
{
	if (!GetOwner()) { return; }
	TankRootMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);

	return;
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTracks::ApplySidewaysForce()
{
	// Calculate sidewasys slip speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work-out required deceleration to correct 
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CounterAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();
	// Calculate and apply sideways force
	auto CounterForce = (TankRootMesh->GetMass() * CounterAcceleration) / 2; //because there's 2 tracks
	TankRootMesh->AddForce(CounterForce);
	return;
}

void UTankTracks::SetThrottle(float Throttle) 
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);
	return;
}

void UTankTracks::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	return;
}

