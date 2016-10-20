// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 = max speed downward, and +1 upward
	void Rotate(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSec = 25.0f;

	
	
	
};
