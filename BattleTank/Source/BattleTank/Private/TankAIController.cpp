// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto tank{ GetControlledTank() };
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *(tank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT possesing a tank"));
	}

	tank = GetPlayerTank();
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController got PlayerController tank: %s"), *(tank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController did NOT get the PlayerController tank"));
	}
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	ATank* ThisTank{ GetControlledTank() };
	ATank* PlayerTank{ GetPlayerTank() };
	if (ThisTank && PlayerTank) {
		ThisTank->AimAt(PlayerTank->GetActorLocation());
	}

}

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	APlayerController* PlayerController { GetWorld()->GetFirstPlayerController() };
	ATank* Tank{ nullptr };

	if (PlayerController) {
		Tank = Cast<ATank>(PlayerController->GetPawn());
	}

	return Tank;
}