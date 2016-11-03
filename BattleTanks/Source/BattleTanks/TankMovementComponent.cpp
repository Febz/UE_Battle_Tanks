// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//no need to call super as we are replacing the functionality

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("%s moving towards: %s"), *TankName, *MoveVelString);
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	auto Name = GetOwner()->GetName();
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	UE_LOG(LogTemp, Warning, TEXT("%s this much throw forward: %f"), *Name, Throw);
	//TODO prevent double speed
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s this much throw right: %f"), *Name, Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	
	//TODO prevent double speed
}
