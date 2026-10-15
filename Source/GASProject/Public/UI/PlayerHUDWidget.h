// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"


class UAbilitySystemComponent;
class UAttributeBarWidget;

/**
 * 
 */
UCLASS()
class GASPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void InitHUD(UAbilitySystemComponent* ASC);

protected:

    //WBP 안에 같은이름
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UAttributeBarWidget> HpBar;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UAttributeBarWidget> StaminaBar;
};
