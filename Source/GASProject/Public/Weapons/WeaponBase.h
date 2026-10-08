// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class GASPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    void SetHitboxEnabled(bool bEnabled);

protected:
    TArray<TObjectPtr<AActor>> HitActors;

};
