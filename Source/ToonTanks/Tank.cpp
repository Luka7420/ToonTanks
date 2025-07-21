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
    
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire); // Bind the Fire action to the "Fire" input
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankPlayerController)// Check if the PlayerControllerRef is valid
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, // Use the visibility channel to check for hits under the cursor
            false, // Whether to trace complex collision
            HitResult); // Get the hit result under the cursor
        RotateTurret(HitResult.ImpactPoint); // Rotate the turret towards the impact point of the hit result
    }

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction(); // Call the base class HandleDestruction function
    SetActorHiddenInGame(true); // Hide the actor in the game
    SetActorTickEnabled(false); // Disable ticking for this actor
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController()); // Get a reference to the player controller 

    
   
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