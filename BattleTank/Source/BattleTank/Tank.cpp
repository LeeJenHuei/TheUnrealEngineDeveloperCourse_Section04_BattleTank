// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"

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
    if (!ensure(TankAimingComponent)) return;
    
    TankAimingComponent->AimAt(HitLocation);//, LaunchSpeed);
}

void ATank::Fire()
{
    if (!ensure(TankAimingComponent)) return;
    
    TankAimingComponent->Fire();
}
