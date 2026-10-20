// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LOPGameplayAbility.generated.h"

/**
 * 
 */
//플레이어 코스트 관련 공통 어빌리티
UCLASS()
class GASPROJECT_API ULOPGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    ULOPGameplayAbility();

protected:
    virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Stamina")
    TSubclassOf<class UGameplayEffect> StaminaRegenBlockEffect;
};
