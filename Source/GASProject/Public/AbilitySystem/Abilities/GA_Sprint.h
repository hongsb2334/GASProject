// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LOPGameplayAbility.h"
#include "GA_Sprint.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UGA_Sprint : public ULOPGameplayAbility
{
	GENERATED_BODY()
	
public:
    UGA_Sprint();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
    //BPGE_Stamina_SprintDrain
    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    TSubclassOf<UGameplayEffect> SprintDrainEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Sprint")
    float SprintSpeed = 900.0f;

    UFUNCTION()
    void OnStaminaEmpty();

private:
    float WalkSpeed = 0.0f;
    FActiveGameplayEffectHandle DrainHandle;
};
