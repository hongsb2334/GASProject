// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API AEnemyCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:
    AEnemyCharacter();

protected:

    virtual void BeginPlay() override;

    //체력바
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
    TObjectPtr<class UWidgetComponent> HpBar;
};
