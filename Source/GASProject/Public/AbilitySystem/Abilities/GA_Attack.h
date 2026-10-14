// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UGA_Attack : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

    UGA_Attack();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    
    

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TSubclassOf<class UGameplayEffect> HitEffect;

    UFUNCTION()
    void OnMontageFinished();

    UFUNCTION()
    void OnMontageCancelled();

    UFUNCTION()
    void OnHitEvent(FGameplayEventData Payload);

    UFUNCTION()
    void OnComboInput(FGameplayEventData Payload);

    UFUNCTION()
    void OnComboWindowOpen(FGameplayEventData Payload);

    UFUNCTION()
    void OnComboWindowClose(FGameplayEventData Payload);

private:
    void TryNextCombo();

    UPROPERTY()
    TObjectPtr<UAnimMontage> ComboMontage;

    int32 ComboIndex = 0;
    bool bComboWindowOpen = false;
    bool bComboInputBuffered = false;

};
