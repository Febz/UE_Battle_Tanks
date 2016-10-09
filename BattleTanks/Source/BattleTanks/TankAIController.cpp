// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AITank = GetAITank();
	PlayaTank = GetPlayerTank();
	if (!AITank)
		UE_LOG(LogTemp, Error, TEXT("404 AI Tank not found"));
	if (!PlayaTank)
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
	if (GetPlayerTank()) 
	{
		AITank->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetAITank() const
{
	auto TankPawn = GetPawn();
	if (!TankPawn) { return nullptr; }
	return Cast<ATank>(TankPawn);
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

