// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"
#include "AttributeBarWidget.generated.h"
/**
 *  // 공통 프로그레스 바에 사용할 시스템 
 */

class UAbilitySystemComponent;
class UProgressBar;
struct FOnAttributeChangeData;


UCLASS()
class GASPROJECT_API UAttributeBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    //ASC에 연결
    UFUNCTION(BlueprintCallable)
    void BindToAbilitySystem(UAbilitySystemComponent* InASC);

protected:
    virtual void NativeDestruct() override;

    //프로그레스 바 색 설정
    virtual void NativePreConstruct() override;

    UPROPERTY(EditAnywhere, Category = "Appearance")
    FLinearColor FillColor = FLinearColor::Red;

    UPROPERTY(EditAnywhere, Category = "Appearance")
    FLinearColor BackGroundColor = FLinearColor(0.05f, 0.05f, 0.05f, 0.8f);



    //bp에서 추가 연출 필요할 시 사용
    UFUNCTION(BlueprintImplementableEvent, Category = "Attribute")
    void OnAttributeUpdated(float value, float MaxValue);

    //표시할 어트리뷰트(인스턴스 or Class Defaults에서 선택)
    UPROPERTY(EditAnywhere, Category = "Attribute")
    FGameplayAttribute Attribute;
    
    UPROPERTY(EditAnywhere, Category = "Attribute")
    FGameplayAttribute MaxAttribute;
    
    //WBP 안의 "Bar"라는 ProgressBar와 자동 연결
    UPROPERTY(meta = (BindWidgetOptional))
    TObjectPtr <UProgressBar> Bar;

private:
    void HandleAttributeChanged(const FOnAttributeChangeData& Data);
    void Refresh();
    void Unbind();

    TWeakObjectPtr<UAbilitySystemComponent> BoundASC;
    FDelegateHandle ValueHandle;
    FDelegateHandle MaxHandle;


};
