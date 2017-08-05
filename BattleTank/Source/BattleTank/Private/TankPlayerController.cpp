// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto tank{ GetControlledTank() };
	if (tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(tank->GetName()));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController NOT possesing a tank"));
	}

}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController ticking at: %f"), DeltaSeconds);
}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

// Get world location of the linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightTraceHitLocation(FVector& OutHitLocation) const {

	/* 1º) Find the crosshair position
	We are going to find the 2D coordinates were the white aiming dot sits in our screen.
	Note that the proper way of doing this would be to get those coordinates from the UI Widget (i.e. the aiming dot)
	itself. But get a hold of that Widget Blueprint and get its absolute viewport coordinates IT'S A FUCKING NIGHTMARE,
	e.g. UMG (Unreal Motion Graphics), Slate, UUserWidget, SUserWidget, and all the mess.

	So, we just hardcoded some folks.
	*/
	int32 ViewportSizeX, ViewportSizeY;
	// Gets the size of the HUD canvas for this player controller. Returns 0 if there is no HUD
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// We hardcoded the widget (x,y) relative position.
	auto ScreenLocation{ FVector2D{ ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation } };
	
	/* 2º) "De-project" the screen position of the crosshair to a world direction
	*/
	FVector CameraWorldLocation, LookWorldDirection;
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X,
										ScreenLocation.Y,
										CameraWorldLocation,
										LookWorldDirection)) {
		return false;
	}
	FVector CrosshairEndLimit{ CameraWorldLocation + LookWorldDirection * CROSSHAIR_REACH };

	/* 3) Line-trace along that look direction, and see what we hit (up to max range)
	*/
	FHitResult HitResult;
	// Complex collision will be used. Player's tank will be ignored
	FCollisionQueryParams CollisionParameters{ FName{ TEXT("Crosshair") }, true, GetPawn() };
	/*
	For the star location of the Line-trace we are using the camera location returned by "DeprojectScreenPositionToWorld()".
	This is the position 'in the lens' of the camera.

	We could equally use "GetPlayerViewPoint(CameraViewPoint, )" or "PlayerCameraManager->GetCameraLocation()".
	Which is a few centimeters backwards, the position 'in the center mass' of the camera.
	*/
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
											 CameraWorldLocation,
											 CrosshairEndLimit,
											 ECollisionChannel::ECC_Camera,		// The instructor used: ECollisionChannel::ECC_Visibility
											 CollisionParameters)) {
		OutHitLocation = HitResult.ImpactPoint;		// The instructor used: HitResult.Location
		return true;
	} else {
		return false;
	}
}

void ATankPlayerController::AimTowardsCrosshair() {

	ATank* ThisTank{ GetControlledTank() };
	if (!ThisTank) {
		return;
	}
	
	FVector HitLocation;
	if (GetSightTraceHitLocation(HitLocation)) {
		ThisTank->AimAt(HitLocation);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("NOTHING is being hit"));
	}
	// If it hits the landscape
		// Tell the controlled tank to aim at this poing
}