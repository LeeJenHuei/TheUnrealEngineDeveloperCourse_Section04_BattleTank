// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    
    // ...
}

// Called when the game starts
void UTankTrack::BeginPlay()
{
    Super::BeginPlay();

    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// Called every frame
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    // Drive the tracks
    DriveTrack();

    // Apply sideway force
    ApplySidewaysForce();
    
    // Reset Throttle
    CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    
    // work-out the required acceleration this frame to correct
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    
    // Calculate and apply sideways for (F = m a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;  // Two tracks
    
    TankRoot->AddForce(CorrectionForce);
}
