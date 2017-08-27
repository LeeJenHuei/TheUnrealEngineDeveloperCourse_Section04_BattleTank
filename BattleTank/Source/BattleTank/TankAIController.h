// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
    void BeginPlay() override;
    void Tick(float DeltaTime);
    
protected:
    // How close can a tank gets to player
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 8000;
};
