// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/LOPGameplayAbility.h"
#include <GameplayEffect.h>

ULOPGameplayAbility::ULOPGameplayAbility()
{
    //몽타주/태스크 콜백 받기 위해 인스턴스 정책 설정(캐릭터마다 어빌리티 인스턴스 재사용)
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULOPGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
    Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

    //코스트가 존재하는 어빌리티만 리젠 지연
    if(GetCostGameplayEffect() && StaminaRegenBlockEffect)
    {
        ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, StaminaRegenBlockEffect.GetDefaultObject(), GetAbilityLevel(Handle, ActorInfo));
    }
}
