// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UAnimMontage;

UCLASS()
class GASPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
    
    UAnimMontage* GetComboMontage() const { return ComboMontage; }

    UFUNCTION(BlueprintCallable)
    void SetHitboxEnabled(bool bEnabled);

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    

protected:
    UPROPERTY()
    TArray<TObjectPtr<AActor>> HitActors;

    UPROPERTY(EditDefaultsOnly, Category = "Combo")
    TObjectPtr<UAnimMontage> ComboMontage;

};
