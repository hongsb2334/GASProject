// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Attack.h"
#include <GameFramework/Character.h>
#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>
#include <Abilities/Tasks/AbilityTask_WaitGameplayEvent.h>
#include <AbilitySystemGlobals.h>
#include <AbilitySystemComponent.h>
#include <LOPGameplayTags.h>
UGA_Attack::UGA_Attack()
{
    //몽타주/태스크 콜백 받기 위해 인스턴스 정책 설정(캐릭터마다 어빌리티 인스턴스 재사용)
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    //ability tag 관련
    FGameplayTagContainer AssetTags;
    AssetTags.AddTag(LOPGameplayTags::Character_Ability_Attack);
    SetAssetTags(AssetTags);

    //공격 중 상태 태그
    ActivationOwnedTags.AddTag(LOPGameplayTags::Character_State_Attacking);

    //
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Attacking);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Dead);

}

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());

    if (!Character || !AttackMontage)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    //BP의 PlayMontageAndWait
    UAbilityTask_PlayMontageAndWait* MontageTask = 
        UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("AttackTask"), AttackMontage);

    MontageTask->OnCompleted.AddDynamic(this, &UGA_Attack::OnMontageFinished);
    MontageTask->OnBlendOut.AddDynamic(this, &UGA_Attack::OnMontageFinished);
    MontageTask->OnInterrupted.AddDynamic(this, &UGA_Attack::OnMontageCancelled);
    MontageTask->OnCancelled.AddDynamic(this, &UGA_Attack::OnMontageCancelled);
    MontageTask->ReadyForActivation();

    UAbilityTask_WaitGameplayEvent* HitTask = 
        UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LOPGameplayTags::Event_Attack_Hit, nullptr, false, true);
    HitTask->EventReceived.AddDynamic(this, &UGA_Attack::OnHitEvent);
}

void UGA_Attack::OnMontageFinished()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_Attack::OnMontageCancelled()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UGA_Attack::OnHitEvent(FGameplayEventData Payload)
{
    UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Payload.Target);
    if (!TargetASC || !HitEffect)
    {
        return;
    }

    const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(HitEffect, GetAbilityLevel());
    if (SpecHandle.IsValid())
    {
        GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
    }
    
}
