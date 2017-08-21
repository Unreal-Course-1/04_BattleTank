// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

	// Move the barrel the right amount this frame
	// Given a max elevation speed and the frame rate
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	auto ElevetionChange{ RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds };
	auto RawNewElevation{ RelativeRotation.Pitch + ElevetionChange };

	float Elevation{ FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees) };

	SetRelativeRotation(FRotator{Elevation, 0, 0});

	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel->Elevated called at speed: %f"), GetWorld()->GetTimeSeconds(), RelativeSpeed);
}


