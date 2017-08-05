// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	static constexpr int CROSSHAIR_REACH{144250};

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	ATank* GetControlledTank() const;

	// Return OUT parameter, true if hit landscape
	bool GetSightTraceHitLocation(FVector&) const;

	/*
	Start the tank moving the barrel so that a shot would hit where
	the crosshair intersects the world
	*/
	void AimTowardsCrosshair();
};
