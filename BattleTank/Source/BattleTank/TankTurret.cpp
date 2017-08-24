// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    // Move the turret the right amount this frame
    // Give a max turn speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Rotation = RelativeRotation.Yaw + RotationChange;
    
//    auto NewRotation = FMath::Clamp<float>(RawNewRotation, MaxElevationDegrees, MinElevationDegrees);
    
    SetRelativeRotation(FRotator(0, Rotation, 0));
}


