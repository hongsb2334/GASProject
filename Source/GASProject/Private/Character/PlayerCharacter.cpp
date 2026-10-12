// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"




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

