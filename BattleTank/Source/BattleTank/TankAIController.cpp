// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();    
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    ATank* ControlledTank = Cast<ATank>(GetPawn());

    if (PlayerTank) {
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        ControlledTank->Fire();
    }
}
