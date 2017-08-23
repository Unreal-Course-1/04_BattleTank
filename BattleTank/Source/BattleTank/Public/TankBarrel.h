// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * This is a Static Mesh Component (rather than an Actor Component, hint see inheritance)
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
/*
	1) Not 'ClassGroup = (Custom), ' before 'meta'; see UTankAimingComponent declaration.
	   Yet it still appear grouped under Custom in the blueprint editor. 'Custom' may be just the default.
	2) For hidding categories to the blueprint editor, we use the 'hidecategories' keyword
		UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision") )
*/
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 7;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 30;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = -2;

public:
	// The function takes the relative speed: [-1, 1] i.e. [Max downward, Max upward]
	void Elevate(float);
	
	
};
