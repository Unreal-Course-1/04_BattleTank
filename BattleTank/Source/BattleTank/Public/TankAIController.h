// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/* Refactoring from INHERIT aiming component to LOCAL aiming component
class ATank;	*/
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	 * These were Atank* before
	 */
	APawn* ThisTank{ nullptr };
	APawn* PlayerTank{ nullptr };

	// Refactoring from INHERIT aiming component to LOCAL aiming component
	UTankAimingComponent* AimingComponent{ nullptr };

	UPROPERTY(EditDefaultsOnly, category = "Setup")
	float AcceptanceRadius = 6500; // How close to target the AI Tank should get, in cm.

	// Implementing DMCD (Dynamic MultiCast Delegate)
	virtual void SetPawn(APawn*) override;
	UFUNCTION()
	void OnPossessedPawnDeath();
};
