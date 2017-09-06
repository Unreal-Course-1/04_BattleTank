// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto tank{ GetControlledTank() };
	if (ensure(tank)) {
		auto AimingComponent{ tank->FindComponentByClass<UTankAimingComponent>() };
		if (ensure(AimingComponent)) {
			FoundAimingComponent(AimingComponent);
		}
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

//
bool ATankPlayerController::GetSightTraceHitLocation2(FVector& OutHitLocation) const {

	/* 1º) Same as below (next function).
	 */
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation{ FVector2D{ ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation } };
	/* 2º) Not need to "De-project"
	 */

	/* 3) Line-trace along that look direction, and see what we hit (up to max range)
	 */
	FHitResult HitResult;
	// Simple collision will be used. Player's tank will be ignored
	FCollisionQueryParams CollisionParameters{ FName{ TEXT("Crosshair") }, false, GetPawn() };
	if (GetHitResultAtScreenPosition(ScreenLocation,
									 ECollisionChannel::ECC_Camera,
									 CollisionParameters,
									 HitResult)) {
		OutHitLocation = HitResult.ImpactPoint;
		return true;
	} else {
		return false;
	}
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
	// Simple collision will be used. Player's tank will be ignored
	FCollisionQueryParams CollisionParameters{ FName{ TEXT("Crosshair") }, false, GetPawn() };
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
	if (GetSightTraceHitLocation2(HitLocation)) {
		ThisTank->AimAt(HitLocation);
	//} else {
	//	UE_LOG(LogTemp, Warning, TEXT("%f: NOTHING is being aimed at"), GetWorld()->GetTimeSeconds());
	}
	// If it hits the landscape
		// Tell the controlled tank to aim at this poing
}