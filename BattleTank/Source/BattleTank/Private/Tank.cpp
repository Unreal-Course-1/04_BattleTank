// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
/* 2� - (things differently) MovementComponent won't be inherited
#include "TankMovementComponent.h" */

// Sets default values
ATank::ATank()
{
	/* Removing the Tick() method from ATank. The tank does nothing when ticking
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	*/
	PrimaryActorTick.bCanEverTick = false;
	// No need to protect pointer as added at construction (?)
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName{ "Aiming Component" });
	*/
	/* To do things differently the MovementComponent won't be passed down to the blueprint through inheritance,
	 * but it will be added directly in the blueprint like an own component member. So following line is not necessary:
	 *
	 *	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName{ "Movement Component" });
	 */
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

/* Removing the Tick() method from ATank. The tank does nothing when ticking
// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
/* Refactoring from INHERIT aiming component to LOCAL aiming component
NOTE this has nothing to do with the intended refactoring (I would say)
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/
void ATank::AimAt(FVector HitLocation) {
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}

/* Refactoring from INHERIT aiming component to LOCAL aiming component
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {	// Changed from UStaticMeshComponent to UTankBarrel

	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {

	TankAimingComponent->SetTurretReference(TurretToSet);
}
*/
void ATank::Fire() {

	bool bIsReloaded{ (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds };

	if (Barrel && bIsReloaded) {
		auto Projectile{ GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
															 Barrel->GetSocketLocation(FName{ "Projectile" }),
															 Barrel->GetSocketRotation(FName{ "Projectile" })) };

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
	return;
}