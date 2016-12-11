// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimComponent(UTankAimingComponent* AimComponentRef);

private:

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//gets coordinates and aims toward target
	void AimAtCrosshair();

    //get sight direction to find aim location
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//returns an OUT param with aim location and true if linetrace hits the landscape
	bool GetAimLocation(FVector LookDirection, FVector& AimLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairX = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairY = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;


};
