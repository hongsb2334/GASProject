// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

class AWeaponBase;

UCLASS()
class GASPROJECT_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

    virtual void PostInitializeComponents() override;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return ASC; }

    UFUNCTION()
    AWeaponBase* GetEquippedWeapon() const { return EquippedWeapon; }

protected:
	// Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void InitializeAttributes();
    void GiveInitialAbilities();
    void SpawnDefaultWeapon();

protected:
    

    //어빌리티 시스템 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GAS")
    TObjectPtr<class UAbilitySystemComponent> ASC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
    TArray<TSubclassOf<class UGameplayAbility>> InitialAbilities;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
    TObjectPtr<class UAttributeSetBase> BaseAttributeSet;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    float InitialMaxHealth = 200.0f;


    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<AWeaponBase> DefaultWeaponClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponSocketName = TEXT("RHandWeaponSocket");

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon")
    TObjectPtr<AWeaponBase> EquippedWeapon;


};
