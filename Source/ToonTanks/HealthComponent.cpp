// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken); // Bind the DamageTaken function to the OnTakeAnyDamage event of the owner actor
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)); // Get a reference to the game mode
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;

	Health -= Damage;
	if(Health <= 0.f && ToonTanksGameMode) // Check if ToonTanksGameMode is valid before proceeding
	{
		ToonTanksGameMode->ActorDied(DamagedActor); // Notify the game mode that an actor has died
	}
	
}