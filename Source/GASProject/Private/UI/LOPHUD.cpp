// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LOPHUD.h"
#include "UI/PlayerHUDWidget.h"
#include <AbilitySystemComponent.h>
void ALOPHUD::InitOverlay(UAbilitySystemComponent* ASC)
{
    if (!HUDWidgetClass || !ASC)
    {
        return;
    }

    //위젯은 한번만 생성
    if (!HUDWidget)
    {
        HUDWidget = CreateWidget<UPlayerHUDWidget>(GetOwningPlayerController(), HUDWidgetClass);
        HUDWidget->AddToViewport();
    }

    //ASC 연결은 호출될 때마다 (죽고 나서 리스폰 했을 때 대응)
    HUDWidget->InitHUD(ASC);
}
