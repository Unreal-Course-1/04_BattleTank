// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;	// Forward Declaration. The next comment below will appear in the Unreal Editor when hovering over
class UTankTurret;

// Holds barrel's properties and Elevate barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	/*
	Chaning the 'type' of the variable Barrel when we created the class TankBarrel (: public UStaticMeshComponent)
	
	UStaticMeshComponent* Barrel { nullptr };
	
	*/
	UTankBarrel* Barrel { nullptr };
	UTankTurret* Turret{ nullptr };

	void MoveGunTurretTowards(FVector);

public:	
	void AimAt(FVector, float);

	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel*);	// Changed from UStaticMeshComponent to UTankBarrel
	void SetTurretReference(UTankTurret*);
};
