// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidgetBase.generated.h"

/**
 * 
 */

class UPlayerAttributeSet;

UCLASS()
class GASPROJECT_API UHealthWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintCallable)
    void BindAttributeSet(UPlayerAttributeSet* AttributeSet);

protected:
    UFUNCTION(BlueprintImplementableEvent)
    void OnHealthUpdated(float Health, float MaxHealth);

    UFUNCTION()
    void HandleHealthChanged(float OldValue, float NewValue);

    UFUNCTION()
    void HandleMaxHealthChanged(float OldValue, float NewValue);

    UPROPERTY()
    TObjectPtr<UPlayerAttributeSet> BoundSet;

};
