// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//gets coordinates and aims toward target
	void AimAtCrosshair();

    //get sight direction to find aim location
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//returns an OUT param with aim location and true if linetrace hits the landscape
	bool GetAimLocation(FVector LookDirection, FVector& AimLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairX = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.33333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	ATank* PlayerTank = nullptr;

};
