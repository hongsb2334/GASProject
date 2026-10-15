// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GASPROJECT_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void InitializeAttributes() override;

    UFUNCTION(BlueprintCallable, Category = "Input")
    void HandleAttackInput();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
    TObjectPtr<class UPlayerAttributeSet> PlayerAttributeSet;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    float InitialMaxStamina = 100.0f;

};
