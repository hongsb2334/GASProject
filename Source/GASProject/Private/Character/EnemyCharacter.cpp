// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthWidgetBase.h"


AEnemyCharacter::AEnemyCharacter()
{

    // Widget
    HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
    HpBar->SetupAttachment(GetMesh());
    HpBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
    HpBar->SetWidgetSpace(EWidgetSpace::Screen);
    HpBar->SetDrawSize(FVector2D(150.0f, 20.f));
    HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    //위젯이 아직 생성 전이면 생성
    HpBar->InitWidget();

    if (UHealthWidgetBase* Widget = Cast<UHealthWidgetBase>(HpBar->GetUserWidgetObject()))
    {
        Widget->BindAttributeSet(BaseAttributeSet);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s: HpBar 위젯 바인딩 실패 (Widget Class 확인)"), *GetName());
    }


}
