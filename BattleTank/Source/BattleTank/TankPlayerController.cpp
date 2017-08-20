// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    ATank* Tank = GetControlledTank();
    if (Tank != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Prossessed Tank: %s"), *Tank->GetName());
    } else {
        UE_LOG(LogTemp, Error, TEXT("No Prossessed Tank"));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())
    {
        return;
    }
    
    // Get work location if linetrace through crosshair
    
    // if it hits the landscape
        // Tell controlled tank to aim at this point
}

