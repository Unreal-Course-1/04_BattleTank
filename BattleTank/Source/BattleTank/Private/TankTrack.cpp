// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"	// For GetWorld()

/* We don't need to Tick() anymore
// Does NOT work in the Unreal 4.17.1 engine. Activate the Tick in OnRegister()
// UTankTrack::UTankTrack() {
//	
//	 PrimaryComponentTick.bCanEverTick = true;
//	
// }
//
void  UTankTrack::OnRegister() {

	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplySidewayForce(DeltaTime);

}
*/
void UTankTrack::BeginPlay() {
	
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}
/* We don't need to Tick() anymore
void UTankTrack::ApplySidewayForce(float DeltaTime) {
*/
void UTankTrack::ApplySidewayForce() {
	// Calculating the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work-out the required acceleration this frame to correct
	// We don't need to Tick() anymore (Following line added)
	float DeltaTime{ GetWorld()->GetDeltaSeconds() };
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways for (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
																			   // Apply the force
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack() {

	auto ForceApplied{ GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce };
	auto ForceLocation{ GetComponentLocation() };

	auto TankRoot{ Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()) };
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle) {

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	/*
	if (GetOwner()->GetName() == "Tank_BP_C_0") {
		UE_LOG(LogTemp, Warning, TEXT("OnHit() - CurrentThrottle: %f"), CurrentThrottle);
	}
	*/
	DriveTrack();
	ApplySidewayForce();
	CurrentThrottle = 0;
}
