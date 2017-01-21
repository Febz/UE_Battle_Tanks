// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimComponent(AimingComponent);
	return;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
	return;
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) 
	{
		AimingComponent->AimAt(HitLocation);
	}
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 PviewSizeX, PviewSizeY;
	FVector CameraLocation, LookDirection;
	GetViewportSize(PviewSizeX, PviewSizeY);
	auto ScreenLocation = FVector2D(PviewSizeX * CrosshairX, PviewSizeY * CrosshairY);
	if(DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection))
	{
		return GetAimLocation(LookDirection, HitLocation);
	}
	return false;
	
}

bool ATankPlayerController::GetAimLocation(FVector LookDirection, FVector& AimLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		AimLocation = HitResult.Location;
		return true;
	}
	AimLocation = FVector(0);
	return false;
}


