// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LOPComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API ULOPComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    ULOPComboActionData();

    //섹션 접두사
    UPROPERTY(EditAnywhere, Category = "Name")
    FString MontageSectionNamePrefix;

    ////최대 콤보수(3개)
    //UPROPERTY(EditAnywhere, Category = "ComboData")

};
