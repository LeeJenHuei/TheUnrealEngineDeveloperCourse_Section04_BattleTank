// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    ATank* PlayerTank = GetPlayerTank();
    if (PlayerTank != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController Found PlayerTank: %s"), *PlayerTank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AIController Can't Find PlayerTank."));
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (GetPlayerTank()) {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    APawn *PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (PlayerPawn != nullptr)
    {
        return Cast<ATank>(PlayerPawn);
    }
    return nullptr;
}
