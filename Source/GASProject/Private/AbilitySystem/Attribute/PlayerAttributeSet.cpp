// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "LOPGameplayTags.h"
UPlayerAttributeSet::UPlayerAttributeSet()
{
	
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    //스태미너 클램프
    if (Attribute == GetStaminaAttribute())
    {
        NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxStamina());
    }
}



void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {

        SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

        
    }
}



