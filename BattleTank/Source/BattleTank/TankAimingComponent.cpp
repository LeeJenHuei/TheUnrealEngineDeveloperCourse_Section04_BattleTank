// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "TankBarrel.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    auto OurTankName = GetOwner()->GetName();
    auto BarrelLocation = Barrel->GetComponentLocation();
    
//    UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

    
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FCollisionResponseParams CollisionResponseParams;
    TArray<AActor*> ActorsToIgnore = TArray<AActor*>();
    
    // Calculate the OutLaunchVelocity
    if (UGameplayStatics::SuggestProjectileVelocity(this,
                                                    OutLaunchVelocity,
                                                    StartLocation,
                                                    HitLocation,
                                                    LaunchSpeed,
                                                    false,
                                                    1.f, // CollisionRadius
                                                    0.f, // OverrideGravityZ
                                                    ESuggestProjVelocityTraceOption::DoNotTrace,
                                                    CollisionResponseParams,
                                                    ActorsToIgnore,
                                                    false
        ))
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);

        
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Work-out difference between current barrel rotation, and AimDirection
    auto BarrelRotation = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotation;
    UE_LOG(LogTemp, Warning, TEXT("AimsRotator: %s"), *AimAsRotator.ToString());
    
    
    Barrel->Elevate(5.f);
}
