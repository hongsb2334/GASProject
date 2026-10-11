// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"

#include <AbilitySystemComponent.h>
#include <Abilities/GameplayAbility.h>


// Sets default values
ACharacterBase::ACharacterBase()
{

    //
    ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

    //애트리뷰트 셋
    PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("CharacterAttributeSet"));
    ASC->AddAttributeSetSubobject<UPlayerAttributeSet>(PlayerAttributeSet);


    

}

void ACharacterBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    InitializeAttributes();

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
    ASC->InitAbilityActorInfo(this, this);

    GiveInitialAbilities();

}

void ACharacterBase::InitializeAttributes()
{
    ASC->SetNumericAttributeBase(PlayerAttributeSet->GetMaxHealthAttribute(), InitialMaxHealth);
    ASC->SetNumericAttributeBase(PlayerAttributeSet->GetHealthAttribute(), InitialMaxHealth);
}

void ACharacterBase::GiveInitialAbilities()
{
    for (const TSubclassOf<UGameplayAbility>& Ability : InitialAbilities)
    {
        if (Ability)
        {
            ASC->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
        }
    }
}





