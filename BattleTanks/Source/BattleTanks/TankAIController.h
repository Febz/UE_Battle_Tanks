// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	

	APawn* GetAITank() const;

	APawn* GetPlayerTank() const;

	APawn* AITank = nullptr;
	APawn* PlayaTank = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "AISettings")
		float MinRadius = 4000.0f;
	
};
