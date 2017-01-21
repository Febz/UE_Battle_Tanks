// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() 
{
	//so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
	return;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	return;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) 
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	return;
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.1f);
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool AimAquired = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		AimLocation,
		LaunchSpeed,
		false, 0, 0, //these are default values, write them everytime
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (AimAquired){
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	return;
}



void UTankAimingComponent::MoveBarrel(FVector AimDirect) 
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirect.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	Barrel->Elevate(DeltaRotation.Pitch);
	auto DueYaw = DeltaRotation.Yaw;
	if((DueYaw < 180.0f && DueYaw > 0.0f) || (DueYaw > -180.0f && DueYaw < 0.0f)) //Normal turret rotation
	{
		Turret->Rotate(DueYaw);
		return;
	}
	else 
	{
		if (DueYaw > 0.0f) 
		{
			DueYaw = DueYaw - 360.0f;
		}
		else if (DueYaw < 0.0f)
		{
			DueYaw = 360.0f - DueYaw;
		}
		Turret->Rotate(DueYaw);
		return;
	}// should rotate to 180 if barrel rotation positive or to -180 otherwise
	Turret->Rotate((-1 * (BarrelRotation.Yaw > 0.0f)) * DueYaw);
	return;
}

void UTankAimingComponent::Fire()
{
	
	if (FiringState != EFiringState::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBP)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	return;
}