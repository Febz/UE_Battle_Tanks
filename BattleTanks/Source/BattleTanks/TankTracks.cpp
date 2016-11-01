// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"


void UTankTracks::SetThrottle(float Throttle) 
{
	auto Name = GetName();
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

