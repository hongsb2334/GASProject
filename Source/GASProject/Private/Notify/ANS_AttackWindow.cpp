// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/ANS_AttackWindow.h"
#include "Character/CharacterBase.h"
#include "Weapons/WeaponBase.h"

void UANS_AttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
    SetHitbox(MeshComp, true);

}

void UANS_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);
    SetHitbox(MeshComp, false);
}

void UANS_AttackWindow::SetHitbox(USkeletalMeshComponent* MeshComp, bool bEnabled) const
{
    ACharacterBase* Character = MeshComp ? Cast<ACharacterBase>(MeshComp->GetOwner()) : nullptr;

    AWeaponBase* Weapon = Character ? Character->GetEquippedWeapon() : nullptr;

    if (Weapon)
    {
        Weapon->SetHitboxEnabled(bEnabled);
    }
}
