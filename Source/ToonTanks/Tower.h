// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override; 

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank; // Reference to the tank pawn

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 1000.f; // Range within which the tower can fire at the tank

	FTimerHandle FireRateTimerHandle; // Timer handle for managing fire rate
	float FireRate = 2.f; // Time between shots
	void CheckFireCondition(); // Function to check if the tower can fire at the tank
	
	bool InFireRange();// Function to check if the tank is within fire range of the tower
};
