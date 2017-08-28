// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

    LastFireTime = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
        
    if (RoundsLeft <= 0)
    {
        RoundsLeft = 0;
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}


void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
    Turret = TurretToSet;
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
    Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel && Turret)) return;

    auto OurTankName = GetOwner()->GetName();
    auto BarrelLocation = Barrel->GetComponentLocation();
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bAimResult = UGameplayStatics::SuggestProjectileVelocity(this,
                                                                  OutLaunchVelocity,
                                                                  StartLocation,
                                                                  HitLocation,
                                                                  LaunchSpeed,
                                                                  false,
                                                                  0.f, // CollisionRadius
                                                                  0.f, // OverrideGravityZ
                                                                  ESuggestProjVelocityTraceOption::DoNotTrace  // This parametre must be set, cannot use TraceFullPath
                                                                  );
    // Calculate the OutLaunchVelocity
    if (bAimResult)
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    
    auto BarrelForward = Barrel->GetForwardVector();
    
    return !BarrelForward.Equals(AimDirection, 0.1f);
}

void UTankAimingComponent::Fire()
{

    if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
    {
        if (!ensure(Barrel && ProjectileBlueprint)) return;

        // Spawn a projectile at the socket location on the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
                                                              Barrel->GetSocketLocation(FName("Projectile")),
                                                              Barrel->GetSocketRotation(FName("Projectile")));
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        RoundsLeft--;
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if (!ensure(Barrel && Turret)) return;
    
    // Work-out difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
    
    float Yaw = (FMath::Abs(DeltaRotator.Yaw) < 180) ? DeltaRotator.Yaw : -DeltaRotator.Yaw;
    Turret->Rotate(Yaw);
}
