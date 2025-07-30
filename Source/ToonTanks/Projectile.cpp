// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh")); // Create a static mesh component for the projectile
	RootComponent = ProjectileMesh; 

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")); // Create a projectile movement component
	ProjectileMovementComponent->MaxSpeed = 1300.f; 
	ProjectileMovementComponent->InitialSpeed = 1300.f; 

	//Particle system component for the projectile launch, attached to the root component
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent); 
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); // Bind the OnHit function to the OnComponentHit event
	if(LaunchSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), 1.0, 0.5); // Play the launch sound at the projectile's location
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner(); // Get the owner of the projectile
	if(MyOwner == nullptr) 
	{
		Destroy();
		return;
	} 

	AController* MyOwnerInsitgator = MyOwner->GetInstigatorController(); // Check if the owner has an instigator controller
	UClass* DamageTypeClass = UDamageType::StaticClass(); // Get the damage type class

	if(OtherActor && OtherActor != this && OtherActor != MyOwner) // Ensure the other actor is valid and not the projectile or its owner
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInsitgator, this, DamageTypeClass); // Apply damage to the other actor
		if(HitParticles) 
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation()); // Spawn hit particles at the projectile's location	
		}
		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation()); // Play hit sound at the projectile's location
		}
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass); // Start camera shake effect for the player controller
		}
	}
	Destroy(); // Destroy the projectile after applying damage
}
