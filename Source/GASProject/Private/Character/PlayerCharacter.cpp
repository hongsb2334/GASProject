// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Components/WidgetComponent.h"
#include <AbilitySystemComponent.h>
#include <Abilities/GameplayAbility.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	//애트리뷰트 셋
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("CharacterAttributeSet"));
	ASC->AddAttributeSetSubobject<UPlayerAttributeSet>(PlayerAttributeSet);


	// Widget
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	HpBar->SetDrawSize(FVector2D(150.0f, 20.f));
	HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerPostInitializeComponents();

    ASC->SetNumericAttributeBase(PlayerAttributeSet->GetMaxHealthAttribute(), 200.0f);
    ASC->SetNumericAttributeBase(PlayerAttributeSet->GetHealthAttribute(), 200.0f);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    ASC->InitAbilityActorInfo(this, this);

    for (const TSubclassOf<UGameplayAbility>& Ability : InitialAbilities)
    {
        if (Ability)
        {
            ASC->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
        }
    }
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

