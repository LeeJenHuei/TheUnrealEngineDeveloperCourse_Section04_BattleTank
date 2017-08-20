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
    
    AimTowardsCrosshair();
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
    
    FVector HitLocation; // Out parameter
    
    if (GetSightRayHitLocation(HitLocation))
    {
//       UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
        GetControlledTank()->AimAt(HitLocation);
    }
    
}

// Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
    // Find the crosshair location
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-trace along that look direction, and see what we hit (up to a max range)
        GetLookVectorHitLocation(LookDirection, outHitLocation);
    }
    outHitLocation = FVector(1.f);
    return true;

}

// De-project the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;    // To be discarded
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &outHitLocation) const
{
    FHitResult HitResult;
    
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
    {
        

        return true;
    }
    return false;
}
