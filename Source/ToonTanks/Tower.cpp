// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h" 
#include "kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); 

    if(InFireRange())
    {
        RotateTurret(Tank->GetActorLocation()); 
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction(); // Call the base class destruction
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Get the player pawn (tank) in the game
    
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true); // Set a timer to check fire conditions at the specified rate
}
void ATower::CheckFireCondition()
{
    if(Tank == nullptr)
    {
        return;
    }
    if(InFireRange() && Tank->bAlive) // Check if the tank is within fire range and is alive
    {
        Fire();
    }
}
bool ATower::InFireRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()); // Calculate the distance to the tank
        if(Distance <= FireRange) // If the tank is within fire range
        {
           return true; // Return true if the tank is within fire range
        }
    }
   return false; // Return false if the tank is not within fire range
}