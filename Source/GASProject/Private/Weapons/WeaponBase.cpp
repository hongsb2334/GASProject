// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"
#include "LOPGameplayTags.h"
#include <Abilities/GameplayAbilityTypes.h>
#include <AbilitySystemBlueprintLibrary.h>
// Sets default values
AWeaponBase::AWeaponBase()
{
 	

}

void AWeaponBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
    //GameplayEventData 구현
    FGameplayEventData Payload;
    Payload.Instigator = GetOwner();
    Payload.Target = OtherActor;

    if (GetOwner() != OtherActor && HitActors.Contains(OtherActor))
    {
        HitActors.AddUnique(OtherActor);
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), LOPGameplayTags::Event_Attack_Hit, Payload);
    }
}

void AWeaponBase::SetHitboxEnabled(bool bEnabled)
{
    HitActors.Reset();
    
    ECollisionEnabled::Type NewType = bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;

    TArray<UActorComponent*> Hitboxes = GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("HitBox"));

    for (UActorComponent* Component : Hitboxes)
    {
        UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Component);
        if (Primitive)
        {
            Primitive->SetCollisionEnabled(NewType);
        }
    }
}



