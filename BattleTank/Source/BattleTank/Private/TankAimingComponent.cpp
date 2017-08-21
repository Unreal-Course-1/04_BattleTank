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

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;	JMOR- Not Tick() fuction defined.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

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

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	/* To get the location of a Static Mesh (Component? i.e. part of a Pawn blueprint):

				UStaticMeshComponent* ->GetComponentLocation()
	
	auto BarrelLocation{ Barrel->GetComponentLocation().ToString() };
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(), *HitLocation.ToString(), *BarrelLocation);
	*/

	if (!Barrel) {
		return;
	}
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
		auto AimRotation{ OutTossVelocity.Rotation() };

		MoveGunTurretTowards(AimRotation);

	} else {
		UE_LOG(LogTemp, Warning, TEXT("%f: NO SOLUTION for projectile velocity"), GetWorld()->GetTimeSeconds());
	}

}
/* We will pass the rotation directly.

void UTankAimingComponent::MoveGunTurretTowards(FVector AimDirection) {
*/
void UTankAimingComponent::MoveGunTurretTowards(FRotator AimRotation) {
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