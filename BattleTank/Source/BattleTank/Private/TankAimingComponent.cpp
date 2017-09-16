// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankTurret.h"
#include "TankBarrel.h"	/* We cannot do a Forward Delclaration here, we have to actually include the .h
						   because in the line 58 we are calling a method of the class (so we actually need
						   its code:

										Barrel->GetForwardVector()
						 */
// Refactoring from INHERIT aiming component to LOCAL aiming component
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void  UTankAimingComponent::BeginPlay() {
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	
	if ( (FPlatformTime::Seconds() - LastFireTime) <= ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	} else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	} else {
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (ensure(Barrel)) {
		auto BarrelForward{ Barrel->GetForwardVector().Rotation() };
		return !BarrelForward.Equals(AimRotation, 0.01);
	} else {
		return false;
	}
}

// Refactoring from INHERIT aiming component to LOCAL aiming component
void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) {
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}
/* Refactoring from INHERIT aiming component to LOCAL aiming component
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {	// Changed from UStaticMeshComponent to UTankBarrel
	if (!BarrelToSet) {
		return;
	}
	Barrel = BarrelToSet;
	return;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) {
		return;
	}
	Turret = TurretToSet;
	return;
}
*/
void UTankAimingComponent::AimAt(FVector HitLocation) {
	/* To get the location of a Static Mesh (Component? i.e. part of a Pawn blueprint):

				UStaticMeshComponent* ->GetComponentLocation()
	
	auto BarrelLocation{ Barrel->GetComponentLocation().ToString() };
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *BarrelLocation);
	*/

	if (ensure(Barrel)) {
		FVector OutTossVelocity;
		FVector StartLocation{ Barrel->GetSocketLocation(FName{"Projectile"}) };
		bool bHaveAimSolution{ UGameplayStatics::SuggestProjectileVelocity(this,
																		   OutTossVelocity,
																		   StartLocation,
																		   HitLocation,
																		   LaunchSpeed,
																		   false,
																		   0.f,
																		   0.f,
																		   ESuggestProjVelocityTraceOption::DoNotTrace) };
		if (bHaveAimSolution) {
			/* We don't need the normal vector of the Toss Velocity vector to get the rotation.
			We can just get the rotation directly.

			auto AimDirection{ OutTossVelocity.GetSafeNormal() };

			MoveGunTurretTowards(AimDirection);
			*/
			AimRotation = OutTossVelocity.Rotation();

			MoveGunTurretTowards(AimRotation);

		//} else {
		//	UE_LOG(LogTemp, Warning, TEXT("%f: NO SOLUTION for projectile velocity"), GetWorld()->GetTimeSeconds());
		}
	}
}
/* We will pass the rotation directly.

void UTankAimingComponent::MoveGunTurretTowards(FVector AimDirection) {
*/
void UTankAimingComponent::MoveGunTurretTowards(FRotator AimRotation) {
	if (ensure(Barrel && Turret)) {
		// Work-out difference between current barrel rotation and AimDirection
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		/* We will pass the rotation directly.
		auto AimAsRotator{ AimDirection.Rotation() };
		auto DeltaRotator{ AimAsRotator - BarrelRotator };
		*/
		auto DeltaRotator{ AimRotation - BarrelRotator };

		Barrel->Elevate(DeltaRotator.Pitch);
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

// Refactoring from INHERIT aiming component to LOCAL aiming component
void UTankAimingComponent::Fire() {

	if (FiringState != EFiringState::Reloading) {
		if (ensure(Barrel && ProjectileBlueprint)) {

			auto Projectile{ GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
																 Barrel->GetSocketLocation(FName{ "Projectile" }),
																 Barrel->GetSocketRotation(FName{ "Projectile" })) };

			Projectile->LaunchProjectile(LaunchSpeed);

			LastFireTime = FPlatformTime::Seconds();
		}

	}
	return;
}