// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // Sets default values for this component's properties
    UTankTrack();
    
    // Called every frame
    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
    
    // Sets a Throttle between -1 and 1
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);
	
    // Max force per track, in Newtons
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float TrackMaxDrivingForce = 400000;    // Assume 40 tonnes tank, and 1g acceleration

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
        
private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void ApplySidewaysForce();
    
    void DriveTrack();
    
    float CurrentThrottle = 0;
};
