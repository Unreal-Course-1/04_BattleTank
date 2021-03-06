// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"		// For GetWorld()
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName{ "Projectile Movement Component" });
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName{ "Projectile Static Mesh Component" });
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName{ "Projectile Launch Blast Particle System" });
	// LaunchBlast->AttachTo(RootComponent); <- Deprecate
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName{ "Projectile Impact Blast Particle System" });
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;	// The blast at impact shouldn't be activated at start

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName{ "Explosion Force" });
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Setting a function that will handle the activation of the proper Paticle System when the projectile hits something.
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}
/*
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
void AProjectile::LaunchProjectile(float Speed) {

	//auto Time{ GetWorld()->GetTimeSeconds() };
	//UE_LOG(LogTemp, Warning, TEXT("%f: FIRING!!! at speed: %f"), Time, Speed);
	/*
	 * Remember the ForwardVector of the projectile has the rotation of the barrel when spawning the projectile.
	 *		Tank.cpp line 67
	*/
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	// Let's make the static mesh of the projectiles desappair
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
	// Now we need to destroy the Actor, so it doesn't keep stacking projectiles in memory as we fire them
	// GetWorld()->GetTimerManager(); <- I used the direct function.
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AProjectile::DestroyProjectile, DelayDestroyProjectile);
	// Apply damage to the hit tank
	UGameplayStatics::ApplyRadialDamage(this,
										ProjectileDamage,
										GetActorLocation(),
										ExplosionForce->Radius,
										UDamageType::StaticClass(),
										TArray<AActor*>()	// Damage all actors
	);
	return;
}

void AProjectile::DestroyProjectile() {

	Destroy();
}