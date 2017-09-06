// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked,
};

class UTankBarrel;	// Forward Declaration. The next comment below will appear in the Unreal Editor when hovering over
class UTankTurret;

// Holds barrel's properties and Elevate barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	/*
	Chaning the 'type' of the variable Barrel when we created the class TankBarrel (: public UStaticMeshComponent)
	
	UStaticMeshComponent* Barrel { nullptr };
	
	*/
	UTankBarrel* Barrel { nullptr };
	UTankTurret* Turret{ nullptr };

	// Sets default values for this component's properties
	UTankAimingComponent();

	/* We will pass the rotation directly.
	void MoveGunTurretTowards(FVector);
	*/
	void MoveGunTurretTowards(FRotator);

protected:

	// Keeps the firing status of the main gun to update the widget aiming point color
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

public:	
	void AimAt(FVector, float);

	// Refactoring from INHERIT aiming component to LOCAL aiming component
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	void SetBarrelReference(UTankBarrel*);	// Changed from UStaticMeshComponent to UTankBarrel
	void SetTurretReference(UTankTurret*);
	*/
};
