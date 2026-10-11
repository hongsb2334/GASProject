// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthWidgetBase.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"

void UHealthWidgetBase::BindAttributeSet(UPlayerAttributeSet* AttributeSet)
{
    if (!AttributeSet) return;
    BoundSet = AttributeSet;

    AttributeSet->OnHealthChanged.AddDynamic(this, &UHealthWidgetBase::HandleHealthChanged);
    AttributeSet->OnMaxHealthChanged.AddDynamic(this, &UHealthWidgetBase::HandleMaxHealthChanged);


    OnHealthUpdated(AttributeSet->GetHealth(), AttributeSet->GetMaxHealth());
}

void UHealthWidgetBase::HandleHealthChanged(float OldValue, float NewValue)
{
    OnHealthUpdated(BoundSet->GetHealth(), BoundSet->GetMaxHealth());
}

void UHealthWidgetBase::HandleMaxHealthChanged(float OldValue, float NewValue)
{
    OnHealthUpdated(BoundSet->GetHealth(), BoundSet->GetMaxHealth());
}
