// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// Selecting shortest path
	if (FGenericPlatformMath::Abs(RelativeSpeed) > 180) {
		RelativeSpeed = -(RelativeSpeed - 180);
	} else {
		RelativeSpeed = RelativeSpeed;
	}
/*
	if (GetOwner()->GetName() == "Tank_BP_C_0") {
		UE_LOG(LogTemp, Warning, TEXT("%f : %s -> RelativeSpeed: %f"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), RelativeSpeed)
	}
*/
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	auto RotationChange{ RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds };

	float Rotation{ RelativeRotation.Yaw + RotationChange };
	SetRelativeRotation(FRotator{ 0, Rotation, 0 });
}



