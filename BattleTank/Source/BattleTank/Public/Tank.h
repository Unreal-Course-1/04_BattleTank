// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;	// This does not seem necesary. It still compiles without errors if this line is commented
/* Refactoring from INHERIT aiming component to LOCAL aiming component
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
*/
/* 2º - (things differently) MovementComponent won't be inherited
class UTankMovementComponent; */

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

		/* Refactoring from INHERIT aiming component to LOCAL aiming component
		UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 165000;	// The instructor uses 4000

		UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 4;

		double LastFireTime{ 0 };
		*/
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
protected:
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	*/
	/* 3º - UPROPERTY(BlueprintReadOnly) was added AFTERWARDS of 1º and 2º comments bellow.
	 * It's added so we can get a reference in the Tank Player Controller Blueprint that we can pass
	 * to the Player UI Widget Blueprint, therefore being able to access the state of the barrel
	 * (locked, reload, moving) and adjust the color of the aiming point in the screen.
	 */
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	// Local barrel reference for spawning projectile
	UPROPERTY(BlueprintReadWrite)
	UTankBarrel* ParentBarrel = nullptr;		// TODO Remove
	*/

	/* 1º - Components appear at the left tab in the editor, there is not categories like in the right
	 * details tab, or the contextual menu. So, even though the next doesn't give compilation
	 * errors, it doesn't make sense:
	 *
	 *		UPROPERTY(BlueprintReadOnly, Category = "Movement")
	 */
	 /* 2º - To do things differently the MovementComponent won't be passed down to the blueprint through inheritance,
	 * but it will be added directly in the blueprint like an own component member. So following line is not necessary:
	 *
	 *		UPROPERTY(BlueprintReadOnly)
	 *		UTankMovementComponent* TankMovementComponent = nullptr;
	 */

public:	
	// Sets default values for this pawn's properties
	ATank();
	/* Removing the Tick() method from ATank. The tank does nothing when ticking
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	*/
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	NOTE this first function has nothing to do with the intended refactoring (I would say)
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector);
	
	UFUNCTION(BlueprintCallable, Category = "Custom")
	void Fire();
	*/
	// Called by the engine when Actor damage is delt
	virtual float TakeDamage(float, struct FDamageEvent const &, class AController *, AActor *) override;

	// For the Health bar widget. Return current health as a percentage of starting health, between 0 and 1.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;
};
