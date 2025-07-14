// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();	
	// Function to set up player input bindings
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Function to set up player input bindings

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private: 
	UPROPERTY(VisibleAnywhere, category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, category = "Movement")
	float Speed = 200.0f; 

	UPROPERTY(EditAnywhere, category = "Movement")
	float TurnRate = 45.0f; 

	void Move(float Value);
	void Turn(float Value); 

	APlayerController* PlayerControllerRef; // Reference to the player controller
};
