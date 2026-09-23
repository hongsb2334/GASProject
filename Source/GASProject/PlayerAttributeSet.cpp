// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeSet.h"

UPlayerAttributeSet::UPlayerAttributeSet() : MaxHealth(100.0f)
{
	InitHealth(GetMaxHealth());
}

void UPlayerAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	//MaxHealth 속성이면 체력값을 1과 NewValue 중 최대값으로 설정, 나중에 hp바를 구현할 때 나누는 값으로 자주 사용하기 때문에 0이 되지 않도록 설정, 
	if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max<float>(1.0f, NewValue);
	}
	//현재 체력은 0보다 작으면 안되고, 최대 체력보다 크면 안되기 때문에 클램프로 설정.
	else if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxHealth());
	}
}
