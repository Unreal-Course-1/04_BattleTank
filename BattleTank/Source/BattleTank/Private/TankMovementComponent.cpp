// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	/* Don't check this here. no problem if nullptr is passed, they variables were already nullptr.
	 * Check this before using the variables, so let's comment this here and add it in the functions
	 * below.
	 *
	 * if (!LeftTrackToSet || !RightTrackToSet) {
	 *	return;
	 * }
	 */
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// Not need to call Super as we're replacing the functionality (i.e. actually move the actor)
	
	FVector AIForwardIntention{ MoveVelocity.GetSafeNormal() };
	FVector TankForward{ GetOwner()->GetActorForwardVector().GetSafeNormal() };
	/* The Dot product of two vectors find how parallel to each other they are: 1 -> Parallel, 0 -> Perpendicular
	 * The Dot product of two vectors with magnitudes of 1 gives the cosine of the angle between such vectors.
	 *
	 * We'll use the cosine, [-1,1], to set the forward throtle of the tanks.
	 */
	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForward));
	/* The Cross product of two vectors find how perpendicular to each other they are: 1 -> Perpendicular, 0 -> Parallel
	 * The Dot product of two vectors with magnitudes of 1 gives the sine of the angle between such vectors times the
	 * unit vector perpendicular to the plane defined by such vectors. I.e. sine times the Unit vector -> sine is the length.
	 *
	 * We'll use the cosine, [-1,1], to set the forward throtle of the tanks.
	 *
	 * BE CAREFUL: The operation is NOT commutative (right-hand rule), i.e. the order of the operands matters.
	 */
	IntendTurnRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
