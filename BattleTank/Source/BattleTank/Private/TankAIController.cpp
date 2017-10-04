// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
/* Refactoring from INHERIT aiming component to LOCAL aiming component
#include "Tank.h"	*/
#include "TankAimingComponent.h"
// Implementing DMCD (Dynamic MultiCast Delegate)
#include "Tank.h"
#include "Mortar.h"

// Depends on movement component via pahtfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	// Getting THIS tank
	/* Refactoring from INHERIT aiming component to LOCAL aiming component
	ThisTank = Cast<ATank>(GetPawn());	*/
	ThisTank = GetPawn();
	// Getting the PLAYER tank
	APlayerController* PlayerController{ GetWorld()->GetFirstPlayerController() };
	if (ensure(PlayerController)) {
		/* Refactoring from INHERIT aiming component to LOCAL aiming component
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());	*/
		PlayerTank = PlayerController->GetPawn();
	}
	// Getting the Aiming Component of our tank
	AimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
}

// Implementing DMCD (Dynamic MultiCast Delegate)
void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto PossessedPawn = Cast<ATank>(InPawn);
		if (ensure(PossessedPawn)) {
			PossessedPawn->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedPawnDeath);
		}
	}
}
// Implementing DMCD (Dynamic MultiCast Delegate)
void ATankAIController::OnPossessedPawnDeath() {
	auto Pawn{ GetPawn() };
	if (Pawn) {
		Pawn->DetachFromControllerPendingDestroy();
	}
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (ensure(ThisTank && PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRadius);
		if (ensure(AimingComponent)) {
			AimingComponent->AimAt(PlayerTank->GetActorLocation());

			/* Refactoring from INHERIT aiming component to LOCAL aiming component
			ThisTank->Fire();
			*/
			if (AimingComponent->GetFiringState() == EFiringState::Locked) {
				AimingComponent->Fire();
			}
		}
	}

}
