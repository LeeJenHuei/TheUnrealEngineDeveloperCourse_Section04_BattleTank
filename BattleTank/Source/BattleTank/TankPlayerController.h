// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    void BeginPlay() override;
	
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    

    
private:
    ATank* GetControlledTank() const;

    // Start the tank moving the barrel so that a shot would hit where the crosshair
    // intersetcs the world
    void AimTowardsCrosshair();
    
    // Return an OUT parameter, true if hit landscape
    bool GetSightRayHitLocation(FVector& outHitLocation) const;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    bool GetLookVectorHitLocation(FVector LookDirection, FVector &outHitLocation) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.3333333f;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0f;  // in Centimeters
};
