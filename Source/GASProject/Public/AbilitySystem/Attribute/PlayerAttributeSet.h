// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.h"
#include "AbilitySystemComponent.h"

#include "PlayerAttributeSet.generated.h"




/**
 * 
 */
UCLASS()
class GASPROJECT_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPlayerAttributeSet();

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
    

    ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Stamina);
    ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxStamina);

    //const 상태에서도 바인딩 동작하게 mutable 추가
    UPROPERTY(BlueprintAssignable, Category = "Attribute")
    mutable FAttributeDataChanged OnMaxStaminaChanged;

    //const 상태에서도 바인딩 동작하게 mutable 추가
    UPROPERTY(BlueprintAssignable, Category = "Attribute")
    mutable FAttributeDataChanged OnStaminaChanged;

protected:

    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    FGameplayAttributeData Stamina;

    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    FGameplayAttributeData MaxStamina;



};
