// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {
        GetPawn()->EnableInput(this); // Enable input for the player controller
    }
    else
    {
        GetPawn()->DisableInput(this);  // Disable input for the player controller
    }

    bShowMouseCursor = bPlayerEnabled; // Show or hide the mouse cursor based on player state
}