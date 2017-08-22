// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;	// This does not seem necesary. It still compiles without errors if this line is commented
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 165000;	// The instructor uses 4000

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel{ nullptr };

	float ReloadTimeInSeconds{ 4 };
	double LastFireTime{ 0 };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent{ nullptr };

public:	
	// Sets default values for this pawn's properties
	ATank();
	/* Removing the Tick() method from ATank. The tank does nothing when ticking
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	*/
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector);

	UFUNCTION(BlueprintCallable, Category = Custom)
	void Fire();
};
