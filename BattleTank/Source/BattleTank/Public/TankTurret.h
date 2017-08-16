// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;

public:
	// The function takes the relative speed: [-1, 1] i.e. [Max downward, Max upward]
	void Rotate(float);
	
};
