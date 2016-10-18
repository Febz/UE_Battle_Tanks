// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = GetControlledTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s: Player Tank deployed and ready for battle"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("404 Player Tank not found"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) 
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 PviewSizeX, PviewSizeY;
	FVector CameraLocation, LookDirection;
	GetViewportSize(PviewSizeX, PviewSizeY);
	auto ScreenLocation = FVector2D(PviewSizeX * CrosshairX, PviewSizeY * CrosshairY);
	if(DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection))
	{
		GetAimLocation(LookDirection, HitLocation);
	}
	return true;
	
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

ATank* ATankPlayerController::GetControlledTank() const 
{
	auto TankPawn = GetPawn();
	if (!TankPawn) { return nullptr; }
	return Cast<ATank>(TankPawn);
}

