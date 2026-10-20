// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "AbilitySystem/Attribute/AttributeSetBase.h"
#include "Weapons/WeaponBase.h"
#include <AbilitySystemComponent.h>
#include <Abilities/GameplayAbility.h>
#include <GameplayEffect.h>


// Sets default values
ACharacterBase::ACharacterBase()
{

    //어빌리티 시스템 컴포넌트
    ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

    //애트리뷰트 셋
    BaseAttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("CharacterAttributeSet"));
    ASC->AddAttributeSetSubobject<UAttributeSetBase>(BaseAttributeSet);

    

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
    
    SpawnDefaultWeapon();
    GiveInitialAbilities();
    ApplyInitialEffects();
}

void ACharacterBase::InitializeAttributes()
{
    ASC->SetNumericAttributeBase(BaseAttributeSet->GetMaxHealthAttribute(), InitialMaxHealth);
    ASC->SetNumericAttributeBase(BaseAttributeSet->GetHealthAttribute(), InitialMaxHealth);
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

void ACharacterBase::SpawnDefaultWeapon()
{
    if (!DefaultWeaponClass)
    {
        return;
    }

    //pino bp와 동일 로직
    FActorSpawnParameters Params;

    Params.Owner = this;
    Params.Instigator = this;   
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    Params.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

    EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeaponClass, GetActorTransform(), Params);

    if (EquippedWeapon)
    {
        EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
    }


}

void ACharacterBase::ApplyInitialEffects()
{
    FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
    Context.AddSourceObject(this);

    for (const TSubclassOf<UGameplayEffect>& Effect : InitialEffects)
    {
        if (!Effect)
        {
            continue;
        }

        const FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(Effect, 1.0f, Context);
        if (Spec.IsValid())
        {
            ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
        }
    }
}





