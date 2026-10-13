// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/ANS_ComboWindow.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "LOPGameplayTags.h"

void UANS_ComboWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    //콤보 시작 이벤트 전송
    SendEvent(MeshComp, LOPGameplayTags::Event_Character_ComboWindow_Open);
}

void UANS_ComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    SendEvent(MeshComp, LOPGameplayTags::Event_Character_ComboWindow_Close);
}

void UANS_ComboWindow::SendEvent(USkeletalMeshComponent* MeshComp, const FGameplayTag& EventTag) const
{
    AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;

    UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);
    if (!ASC)
    {
        return;
    }

    FGameplayEventData Payload;
    Payload.EventTag = EventTag;
    Payload.Instigator = Owner;
    ASC->HandleGameplayEvent(EventTag, &Payload);

}
