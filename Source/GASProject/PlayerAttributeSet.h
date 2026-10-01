// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

//델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeDataChanged, float, OldValue, float, NewValue);


/**
 * 
 */
UCLASS()
class GASPROJECT_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPlayerAttributeSet();

	//이 매크로로 속성 하나당 반복 작성해야 하는 함수 4개를 자동 생성(GetHealthAttribute, GetHealth 등 4개를 매 속성마다 작성해줘야 하는데, 이 매크로로 간단히 구현)
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Health);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxHealth);


    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


    //const 상태에서도 바인딩 동작하게 mutable 추가
    UPROPERTY(BlueprintAssignable, Category = "Attribute")
    mutable FAttributeDataChanged OnMaxHealthChanged;

    //const 상태에서도 바인딩 동작하게 mutable 추가
    UPROPERTY(BlueprintAssignable, Category = "Attribute")
    mutable FAttributeDataChanged OnHealthChanged;

protected:

	//현재 체력
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;

	//최대 체력
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;


};
