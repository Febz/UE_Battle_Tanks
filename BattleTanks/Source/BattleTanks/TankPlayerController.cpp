// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
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

}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

}



ATank* ATankPlayerController::GetControlledTank() const 
{
	auto TankPawn = GetPawn();
	if (!TankPawn) { return nullptr; }
	return Cast<ATank>(TankPawn);
}

