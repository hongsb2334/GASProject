// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AttributeBarWidget.h"
#include <AbilitySystemComponent.h>
#include "Components/ProgressBar.h"
void UAttributeBarWidget::BindToAbilitySystem(UAbilitySystemComponent* InASC)
{
    Unbind();

    if (!InASC || !Attribute.IsValid() || !MaxAttribute.IsValid())
    {
        return;
    }
    BoundASC = InASC;

    //값이 바뀔 때마다 호출(Instant,periodic, Duration GE 등 모두)
    ValueHandle = InASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UAttributeBarWidget::HandleAttributeChanged);
    MaxHandle = InASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UAttributeBarWidget::HandleAttributeChanged);

    //연결 직후 현재 값으로 한번 갱신
    Refresh();

}

void UAttributeBarWidget::NativeDestruct()
{
    Unbind();
    Super::NativeDestruct();
}

void UAttributeBarWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (Bar)
    {
        //채워진 부분
        Bar->SetFillColorAndOpacity(FillColor);

        //빈 부분(스타일 복사해서 배경 틴트만 바꾸고 다시적용)
        FProgressBarStyle Style = Bar->GetWidgetStyle();
        Style.BackgroundImage.TintColor = FSlateColor(BackGroundColor);
        Bar->SetWidgetStyle(Style);
    }
}

void UAttributeBarWidget::HandleAttributeChanged(const FOnAttributeChangeData& Data)
{
    Refresh();
}

void UAttributeBarWidget::Refresh()
{
    UAbilitySystemComponent* ASC = BoundASC.Get();
    if (!ASC)
    {
        return;
    }

    bool bFoundValue = false;
    bool bFoundMax = false;
    const float Value = ASC->GetGameplayAttributeValue(Attribute, bFoundValue);
    const float MaxValue = ASC->GetGameplayAttributeValue(MaxAttribute, bFoundMax);

    if (Bar)
    {
        Bar->SetPercent(MaxValue > 0.0f ? Value / MaxValue : 0.0f);
    }

    OnAttributeUpdated(Value, MaxValue);

}

void UAttributeBarWidget::Unbind()
{
    if (UAbilitySystemComponent* ASC = BoundASC.Get())
    {
        ASC->GetGameplayAttributeValueChangeDelegate(Attribute).Remove(ValueHandle);
        ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).Remove(MaxHandle);
    }

    ValueHandle.Reset();
    MaxHandle.Reset();
    BoundASC.Reset();
}
