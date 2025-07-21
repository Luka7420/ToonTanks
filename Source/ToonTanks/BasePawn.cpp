// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}
void ABasePawn::HandleDestruction()
{
	// TODO: VISUAL & SOUND EFFECTS
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); //Or LookAtRotation.Yaw and LookAtRotation.Pitch =0.f;
	TurretMesh->SetWorldRotation( // Set the turret's rotation to face the target
		FMath::RInterpTo(TurretMesh->GetComponentRotation(),// Interpolate the turret's rotation towards the target
		 LookAtRotation, // Current rotation of the turret
		 UGameplayStatics::GetWorldDeltaSeconds(this), // Delta time for smooth rotation
		 25.f)// Interpolation speed
	); 
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation(); 
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>( // Spawn a projectile at the spawn point
		ProjectileClass, 
		Location, 
		Rotation
	);
	Projectile->SetOwner(this); 
}





