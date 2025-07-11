// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // Function to set up player input bindings
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); // Call the base class implementation first
    
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move); // Bind the Move function to the "MoveForward" axis input
}

void ATank::Move(float Value) // Function to handle movement input
{
    FVector DeltaLocation = FVector::ZeroVector; 
    DeltaLocation.X = Value;
    AddActorLocalOffset(DeltaLocation);
    
}