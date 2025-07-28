// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Tank.h" // Include the Tank class header to access its functionality
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
   if(DeadActor == Tank)
   {
      Tank->HandleDestruction(); // Call the HandleDestruction method on the Tank instance
      if(ToonTanksPlayerController)
      {
         ToonTanksPlayerController->SetPlayerEnabledState(false); // Disable player input through the player controller
      }
      GameOver(false); // Call the GameOver method with false indicating the player lost
   }
   else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) // Check if the DeadActor is a Tower
   {
      DestroyedTower->HandleDestruction(); // Call the HandleDestruction method on the Tower instance
      TargetTowers--;
      if(TargetTowers == 0) 
      {
         GameOver(true); 
      }
   }
  
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart(); 

    
}
void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount(); // Get the number of target towers in the game
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Get the player pawn and cast it to ATank
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); // Get the player controller and cast it to AToonTanksPlayerController

    StartGame(); 

    if(ToonTanksPlayerController)
    {
       // Disable player input initially
       ToonTanksPlayerController->SetPlayerEnabledState(false); 

       FTimerHandle PlayerEnableTimerHandle;
       // Create a delegate to enable player input after the start delay
       FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
       GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableDelegate, StartDelay, false); // Set the timer to call the delegate after StartDelay seconds
    }
} 
int32 AToonTanksGameMode::GetTargetTowerCount()
{
   //Find out how many towers are in the world
   TArray<AActor*> TowerActors; // Array to hold all tower actors
   UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowerActors); // Get all actors of class ATower in the world
   return TowerActors.Num(); // Return the number of towers found
}