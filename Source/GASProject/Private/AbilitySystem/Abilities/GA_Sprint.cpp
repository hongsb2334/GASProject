// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Sprint.h"
#include <Gameframework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include <Abilities\Tasks\AbilityTask_WaitGameplayTag.h>
#include <AbilitySystemComponent.h>
#include <GameplayEffect.h>
#include "LOPGameplayTags.h"

UGA_Sprint::UGA_Sprint()
{
    //Sprint 어빌리티에 Character_Ability_Sprint 부여(태그로 어빌리티 구분)
    FGameplayTagContainer AssetTags;
    AssetTags.AddTag(LOPGameplayTags::Character_Ability_Sprint);
    SetAssetTags(AssetTags);

    //달리는 동안 태그 부여
    ActivationOwnedTags.AddTag(LOPGameplayTags::Character_State_Sprinting);

    //이 상태일때는 달리기 불가
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Attacking);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_State_Dead);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_Ability_Dodge);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Character_Ability_Guard);
    ActivationBlockedTags.AddTag(LOPGameplayTags::Stamina_State_Empty);
}

void UGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());

    //예외처리, 캐릭터 캐스팅 실패 or 시작 비용 지불 실패시 어빌리티 종료
    if (!Character || !CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    //원래 속도 따로 저장하고 MaxWalkSpeed 변경
    UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
    WalkSpeed = Movement->MaxWalkSpeed;
    Movement->MaxWalkSpeed = SprintSpeed;

    if (SprintDrainEffect)
    {
        DrainHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, SprintDrainEffect.GetDefaultObject(), GetAbilityLevel());
    }

    //스태미너 비면 실행할 태스크
    UAbilityTask_WaitGameplayTagAdded* StaminaEmptyTask =
        UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(this, LOPGameplayTags::Stamina_State_Empty);
    StaminaEmptyTask->Added.AddDynamic(this, &UGA_Sprint::OnStaminaEmpty);
    StaminaEmptyTask->ReadyForActivation();
}

void UGA_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (IsEndAbilityValid(Handle, ActorInfo))
    {
        ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());

        if (Character && WalkSpeed > 0.0f)
        {
            //어빌리티 활성화 할때 저장해놨던 원래 걷기 속도를 다시 저장, 스프린트 종료시 속도 되돌아옴
            Character->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
        }
        
        //어빌리티 종료시 게임플레이 이펙트 종료 후 핸들 초기화
        if (DrainHandle.IsValid())
        {
            GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(DrainHandle);
            DrainHandle.Invalidate();
        }

        //멈춘 직후에 스태미너 리젠 지연 효과
        if (StaminaRegenBlockEffect)
        {
            ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, StaminaRegenBlockEffect.GetDefaultObject(), GetAbilityLevel());
        }
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_Sprint::OnStaminaEmpty()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
