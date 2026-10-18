// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Attack.h"
#include <GameFramework/Character.h>
#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>
#include <Abilities/Tasks/AbilityTask_WaitGameplayEvent.h>
#include <AbilitySystemGlobals.h>
#include <AbilitySystemComponent.h>
#include <Character/CharacterBase.h>
#include <Weapons/WeaponBase.h>
#include <LOPGameplayTags.h>
UGA_Attack::UGA_Attack()
{
    

    //ability tag 관련
    FGameplayTagContainer AssetTags;
    AssetTags.AddTag(LOPGameplayTags::Character_Ability_Attack);
    SetAssetTags(AssetTags);

    //공격 중 상태 태그
    ActivationOwnedTags.AddTag(LOPGameplayTags::Character_State_Attacking);

    //공격 실행중, 회피, 죽음 상태일 때 공격 못하게
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Attacking);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Dodging);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Dead);

    //공격 시작시 스프린트 종료
    CancelAbilitiesWithTag.AddTag(LOPGameplayTags::Character_Ability_Sprint);

}

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    //무기마다의 몽타주 가져오기
    ACharacterBase* Character = Cast<ACharacterBase>(GetAvatarActorFromActorInfo());
    AWeaponBase* Weapon = Character ? Character->GetEquippedWeapon() : nullptr;
    ComboMontage = Weapon ? Weapon->GetComboMontage() : nullptr;

    if (!ComboMontage || !CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    //InstancedPerActor라 이전 실행 값이 남아있어서 초기화
    ComboIndex = 0;
    bComboWindowOpen = false;
    bComboInputBuffered = false;

    //BP의 PlayMontageAndWait
    UAbilityTask_PlayMontageAndWait* MontageTask = 
        UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("AttackTask"), ComboMontage, 1.0f, ComboMontage->GetSectionName(0));

    MontageTask->OnCompleted.AddDynamic(this, &UGA_Attack::OnMontageFinished);
    MontageTask->OnBlendOut.AddDynamic(this, &UGA_Attack::OnMontageFinished);
    MontageTask->OnInterrupted.AddDynamic(this, &UGA_Attack::OnMontageCancelled);
    MontageTask->OnCancelled.AddDynamic(this, &UGA_Attack::OnMontageCancelled);
    MontageTask->ReadyForActivation();

    
    UAbilityTask_WaitGameplayEvent* HitTask = 
        UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LOPGameplayTags::Event_Attack_Hit, nullptr, false, true);
    HitTask->EventReceived.AddDynamic(this, &UGA_Attack::OnHitEvent);
    HitTask->ReadyForActivation();

    //콤보 입력 이벤트
    UAbilityTask_WaitGameplayEvent* InputTask =
        UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LOPGameplayTags::Event_Character_ComboInput, nullptr, false, true);
    InputTask->EventReceived.AddDynamic(this, &UGA_Attack::OnComboInput);
    InputTask->ReadyForActivation();

    //콤보 윈도우 open/close 이벤트
    UAbilityTask_WaitGameplayEvent* ComboOpenTask =
        UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LOPGameplayTags::Event_Character_ComboWindow_Open, nullptr, false, true);
    ComboOpenTask->EventReceived.AddDynamic(this, &UGA_Attack::OnComboWindowOpen);
    ComboOpenTask->ReadyForActivation();

    UAbilityTask_WaitGameplayEvent* ComboCloseTask =
        UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LOPGameplayTags::Event_Character_ComboWindow_Close, nullptr, false, true);
    ComboCloseTask->EventReceived.AddDynamic(this, &UGA_Attack::OnComboWindowClose);
    ComboCloseTask->ReadyForActivation();
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

void UGA_Attack::OnComboInput(FGameplayEventData Payload)
{
    bComboInputBuffered = true;
    TryNextCombo();
}

void UGA_Attack::OnComboWindowOpen(FGameplayEventData Payload)
{
    bComboWindowOpen = true;
    TryNextCombo();
}

void UGA_Attack::OnComboWindowClose(FGameplayEventData Payload)
{
    bComboWindowOpen = false;
}

void UGA_Attack::TryNextCombo()
{
    //콤보 윈도우가 오픈되지 않았거나, 선입력이 없었거나, 콤보 몽타주가 없는 경우 리턴
    if (!bComboWindowOpen || !bComboInputBuffered || !ComboMontage)
    {
        return;
    }

    const int32 NextIndex = (ComboIndex + 1) % ComboMontage->GetNumSections();


    //다음 코스트 지불
    if (!CommitAbilityCost(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
    {
        return;
    }

    if (UAnimInstance* AnimInstance = CurrentActorInfo->GetAnimInstance())
    {
        //약공격 3타 ->1타 어색한거 보간
        AnimInstance->RequestSlotGroupInertialization(TEXT("DefaultGroup"), 0.2f);
    }
    //콤보 ANS 구간 안에 입력이 들어오면 다음 콤보 섹션으로 점프
    MontageJumpToSection(ComboMontage->GetSectionName(NextIndex));

    //다음 상태로 이동
    ComboIndex = NextIndex;
    bComboWindowOpen = false;
    bComboInputBuffered = false;
}
