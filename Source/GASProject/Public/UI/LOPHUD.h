// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LOPHUD.generated.h"

class UAbilitySystemComponent;
class UPlayerHUDWidget;
/**
 * 
 */
UCLASS()
class GASPROJECT_API ALOPHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    void InitOverlay(UAbilitySystemComponent* ASC);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UPlayerHUDWidget> HUDWidgetClass;

private:
    UPROPERTY()
    TObjectPtr<UPlayerHUDWidget> HUDWidget;
};
