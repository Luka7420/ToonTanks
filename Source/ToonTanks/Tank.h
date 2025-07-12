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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Function to set up player input bindings
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
};
