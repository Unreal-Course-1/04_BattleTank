// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
	/* Removing the Tick() method from ATank. The tank does nothing when ticking
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	*/
	PrimaryActorTick.bCanEverTick = false;
	// No need to protect pointer as added at construction (?)
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
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
// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) {

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {	// Changed from UStaticMeshComponent to UTankBarrel

	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {

	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("FIRING MOTHERFUCKER!!!"));
	return;
}