// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	if(bHaveAimSolution) {
		auto AimDirection{ OutTossVelocity.GetSafeNormal() };

		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator{ AimDirection.Rotation() };
	auto DeltaRotator{ AimAsRotator - BarrelRotator };

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());
	// Move the barrel the right amount this frame
	// Given a max elevation speed and the frame rate


	// Get static mesh for barrel
	// Get static mesh for turret
	// Calculate pitch movement for barrel
	// Calculate yaw movement for turret
	// Set new values
}
