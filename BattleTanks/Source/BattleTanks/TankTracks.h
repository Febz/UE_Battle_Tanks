// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * Used to set maximum driving force and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
	//Max force per track in newton
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxForce = 20000000; //assumed 40 tonne tank
	
private:

	UTankTracks();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();
	
	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UStaticMeshComponent* TankRootMesh = nullptr;
	UPrimitiveComponent* TankRoot = nullptr;

	float CurrentThrottle = 0.0f;
};
