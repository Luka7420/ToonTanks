// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Tank.h" // Include the Tank class header to access its functionality
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
   if(DeadActor == Tank)
   {
      Tank->HandleDestruction(); // Call the HandleDestruction method on the Tank instance
      if(Tank->GetTankPlayerController())
      {
         Tank->DisableInput(Tank->GetTankPlayerController()); // Disable input for the player controller associated with the tank
         Tank->GetTankPlayerController()->bShowMouseCursor = false; // Hide the mouse cursor for the player controller
      }
   }
   else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) // Check if the DeadActor is a Tower
   {
      DestroyedTower->HandleDestruction(); // Call the HandleDestruction method on the Tower instance
   }
  
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Get the player pawn and cast it to ATank
}