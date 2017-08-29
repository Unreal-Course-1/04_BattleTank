// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	// Getting THIS tank
	ThisTank = Cast<ATank>(GetPawn());
	if (!ThisTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT possesing a tank"));
	}
	// Getting the PLAYER tank
	APlayerController* PlayerController{ GetWorld()->GetFirstPlayerController() };
	if (PlayerController) {
		PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	}

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController did NOT get the PlayerController tank"));
	}
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if (ThisTank && PlayerTank) {

		MoveToActor(PlayerTank, AcceptanceRadius);

		ThisTank->AimAt(PlayerTank->GetActorLocation());

		ThisTank->Fire();
	}

}
