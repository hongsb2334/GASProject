// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "LOPGameplayTags.h"
UPlayerAttributeSet::UPlayerAttributeSet()
{
	
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    if (Attribute == GetMaxStaminaAttribute())
    {
        NewValue = FMath::Max<float>(1.0f, NewValue);
    }

    //스태미너 클램프
    if (Attribute == GetStaminaAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxStamina());
    }
}

void UPlayerAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetMaxStaminaAttribute())
    {
        OnMaxStaminaChanged.Broadcast(OldValue, NewValue);
    }
    else if (Attribute == GetStaminaAttribute())
    {
        OnStaminaChanged.Broadcast(OldValue, NewValue);
    }
}



void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

        UAbilitySystemComponent& TargetASC = Data.Target;
        //스태미너가 다 떨어지면 Empty 태그 부여
        TargetASC.SetLooseGameplayTagCount(LOPGameplayTags::Stamina_State_Empty, GetStamina() <= 0.0f ? 1 : 0);

    }

    
}



