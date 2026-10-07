// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Attack.h"
#include <GameFramework/Character.h>
#include <LOPGameplayTags.h>
UGA_Attack::UGA_Attack()
{
    //몽타주/태스크 콜백 받기 위해 인스턴스 정책 설정(캐릭터마다 어빌리티 인스턴스 재사용, 굳이 없어도 되지 않나 생각중)
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


}

void UGA_Attack::OnMontageFinished()
{
}

void UGA_Attack::OnMontageCancelled()
{
}

void UGA_Attack::OnHitEvent(FGameplayEventData Payload)
{
}
