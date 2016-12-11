// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = GetAITank();
	PlayaTank = GetPlayerTank();
	if (!ensure(AITank))
		UE_LOG(LogTemp, Error, TEXT("404 AI Tank not found"));
	if (!ensure(PlayaTank))
	{
		UE_LOG(LogTemp, Error, TEXT("AI Tank couldn't find Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: AI Tank deployed and ready for battle. Enemy player located: %s"), *AITank->GetName(), *PlayaTank->GetName());
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(PlayaTank && AITank)) { return; }
	

	MoveToActor(PlayaTank, MinRadius);

	auto AimComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	
	AimComponent->AimAt(PlayaTank->GetActorLocation());

	
	AimComponent->Fire();
	
	
}



APawn* ATankAIController::GetAITank() const
{
	auto TankPawn = GetPawn();
	if (!TankPawn) { return nullptr; }
	return TankPawn;
}

APawn* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return PlayerPawn;
}

