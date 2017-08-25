// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP BeginPlay() to work
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetAimingComponent(UTankAimingComponent* ComponentToSet)
{
    TankAimingComponent = ComponentToSet;
}

void ATank::AimAt(FVector HitLocation)
{
    if (TankAimingComponent == nullptr) return;
    
    TankAimingComponent->AimAt(HitLocation);//, LaunchSpeed);
}
/*
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
//    TankAimingComponent->SetBarrelReference(BarrelToSet);
//    Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
//    TankAimingComponent->SetTurretReference(TurretToSet);
}
*/
void ATank::Fire()
{
    if (TankAimingComponent == nullptr) return;
    
    TankAimingComponent->Fire();
/*
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    if (Barrel && isReloaded)
    {
    
        // Spawn a projectile at the socket location on the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
                                                              Barrel->GetSocketLocation(FName("Projectile")),
                                                              Barrel->GetSocketRotation(FName("Projectile")));
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
 */
}
