// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "UI/AttributeBarWidget.h"
#include "AbilitySystemComponent.h"

void UPlayerHUDWidget::InitHUD(UAbilitySystemComponent* ASC)
{
    HpBar->BindToAbilitySystem(ASC);
    StaminaBar->BindToAbilitySystem(ASC);
}
