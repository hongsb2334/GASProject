// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/LOPAnimInstance.h"
#include "AbilitySystemGlobals.h"
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

void ULOPAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningActor()))
    {
        GameplayTagPropertyMap.Initialize(this, ASC);
    }

}

void ULOPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (const ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner()))
    {
        //이동 입력이 있는지
        bHasAcceleration = !Character->GetCharacterMovement()->GetCurrentAcceleration().IsNearlyZero();
    }

}
