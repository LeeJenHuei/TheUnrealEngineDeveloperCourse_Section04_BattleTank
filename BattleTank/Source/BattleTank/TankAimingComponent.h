// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Locked,
    Aiming,
    Reloading
};


// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;


// Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void SetTurretReference(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;

    
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void AimAt(FVector HitLocation);//, float LaunchSpeed);
    void Fire();
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;  /// Sensible starting value of 1000m/s
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    
    void MoveBarrelTowards(FVector AimDirection);
    
    double LastFireTime = 0;
};
