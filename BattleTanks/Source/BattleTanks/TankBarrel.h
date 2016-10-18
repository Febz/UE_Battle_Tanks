// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 = max speed downward, and +1 upward
	void Elevate(float RelativeSpeed);
	
private:

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSec = 10.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 40.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0.0f;
};
