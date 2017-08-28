// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
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
    
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;    
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;  /// Sensible starting value of 4m/s
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 RoundsLeft = 3;

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void SetTurretReference(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Control")
    void Fire();
    
    void AimAt(FVector HitLocation);
    
    EFiringState GetFiringState() const;
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int32 GetRoundsLeft() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
    

    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    double LastFireTime = 0;
    FVector AimDirection;
    
    
    void MoveBarrelTowards(FVector AimDirection);
    bool IsBarrelMoving();
};
