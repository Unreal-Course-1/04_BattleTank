// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	/* We don't need to Tick() anymore
	// Does NOT work in the Unreal 4.17.1 engine. Activate the Tick in OnRegister()
	// UTankTrack();
	//
	virtual void OnRegister() override;

	virtual void TickComponent(float, enum ELevelTick, FActorComponentTickFunction *) override;

	void ApplySidewayForce(float DeltaTime);
	*/
	void ApplySidewayForce();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();
	float CurrentThrottle{ 0 };

public:
	// Sets throttle
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f;	// Assume 40 tonne tank and 1g acceleration   400000 40000000.f, 

};
