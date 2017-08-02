// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto tank{ GetControlledTank() };
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *(tank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController NOT possesing a tank"));
	}

}

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}