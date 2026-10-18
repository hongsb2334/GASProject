// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayEffectTypes.h"
#include "LOPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API ULOPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;


    //태그가 붙거나 떨어질 때 ABP에서의 변수를 자동으로 갱신
    UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
    FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    bool bHasAcceleration = false;


};
