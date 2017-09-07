// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
/* Refactoring from INHERIT aiming component to LOCAL aiming component
class ATank;
*/
class UTankAimingComponent;
/**
 * Responsible for helping the player aim.
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

	// Another way to get the hit location of the crosshair aiming point
	bool GetSightTraceHitLocation2(FVector&) const;
	// Return OUT parameter, true if hit landscape
	bool GetSightTraceHitLocation(FVector&) const;

	UTankAimingComponent* AimingComponent{ nullptr };

	/*
	Start the tank moving the barrel so that a shot would hit where
	the crosshair intersects the world
	*/
	void AimTowardsCrosshair();

protected:
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

public:
	ATankPlayerController();
};
