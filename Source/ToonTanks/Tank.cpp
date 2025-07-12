// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn); // Bind the Turn function to the "Turn" axis input
}

void ATank::Move(float Value) // Function to handle movement input
{
    FVector DeltaLocation = FVector::ZeroVector; 
    // X = Value * DeltaTime * Speed;
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); // Calculate the change in location based on input value, speed, and delta time
    AddActorLocalOffset(DeltaLocation, true);   
}

void ATank::Turn(float Value) 
{
    FRotator DeltaRotation = FRotator::ZeroRotator; 
    // Yaw = Value * DeltaTime * TurnRate;
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this); // Calculate the change in rotation based on input value, speed, and delta time
    AddActorLocalRotation(DeltaRotation, true); // Apply the rotation to the actor
}