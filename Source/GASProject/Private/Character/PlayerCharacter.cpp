// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "UI/LOPHUD.h"
#include <GameFramework/PlayerController.h>
#include <LOPGameplayTags.h>



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

    //플레이어 애트리뷰트 셋 추가 
    PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
    ASC->AddAttributeSetSubobject<UPlayerAttributeSet>(PlayerAttributeSet);

    
	
}



// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ALOPHUD* LOPHUD = PC->GetHUD<ALOPHUD>())
        {
            LOPHUD->InitOverlay(ASC);
        }
    }
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::InitializeAttributes()
{
    Super::InitializeAttributes();


    ASC->SetNumericAttributeBase(PlayerAttributeSet->GetMaxStaminaAttribute(), InitialMaxStamina);
    ASC->SetNumericAttributeBase(PlayerAttributeSet->GetStaminaAttribute(), InitialMaxStamina);
}

void APlayerCharacter::HandleMovingStart()
{
    if (ASC)
    {
        //움직임 시작되면 움직임 태그 부여
        ASC->SetLooseGameplayTagCount(LOPGameplayTags::Character_State_Moving, 1);
    }

}

void APlayerCharacter::HandleMovingEnd()
{
    if (ASC)
    {
        //움직임 종료시 태그 제거
        ASC->SetLooseGameplayTagCount(LOPGameplayTags::Character_State_Moving, 0);
    }

}

void APlayerCharacter::HandleAttackInput()
{
    if (!ASC)
    {
        return;
    }

    //현재 공격중 상태이면 GA_Attack에 콤보 입력 전달
    if (ASC->HasMatchingGameplayTag(LOPGameplayTags::Character_State_Attacking))
    {
        FGameplayEventData Payload;
        Payload.EventTag = LOPGameplayTags::Event_Character_ComboInput;
        Payload.Instigator = this;

        ASC->HandleGameplayEvent(Payload.EventTag, &Payload);
    }
    else
    {
        //공격중 상태 아니면 공격 시작
        FGameplayTagContainer AttackTags(LOPGameplayTags::Character_Ability_Attack);
        ASC->TryActivateAbilitiesByTag(AttackTags);
    }
}

void APlayerCharacter::HandleSprintStart()
{
    if (!ASC)
    {
        return;
    }

    FGameplayTagContainer SprintTags(LOPGameplayTags::Character_Ability_Sprint);
    ASC->TryActivateAbilitiesByTag(SprintTags);
}

void APlayerCharacter::HandleSprintEnd()
{
    if (!ASC)
    {
        return;
    }

    FGameplayTagContainer SprintTags(LOPGameplayTags::Character_Ability_Sprint);
    ASC->CancelAbilities(&SprintTags);
}

