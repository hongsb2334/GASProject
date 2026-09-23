// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
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

	//이 매크로로 속성 하나당 반복 작성해야 하는 함수 4개를 자동 생성(GetHealthAttribute, GetHealth 등 4개를 매 속성마다 작성해줘야 하는데, 이 매크로로 간단히 구현)
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Health);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxHealth);

	//사전 속성값 변경
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const;

protected:

	//현재 체력
	UPROPERTY(BlueprintReadOnly, Category = "Health");
	FGameplayAttributeData Health;

	//최대 체력
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;


};
