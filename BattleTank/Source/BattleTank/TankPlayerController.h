// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
    ATank* GetControlledTank() const;
    
    void BeginPlay() override;
	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Start the tank moving the barrel so that a shot would hit where the crosshair
    // intersetcs the world
    void AimTowardsCrosshair();
};
