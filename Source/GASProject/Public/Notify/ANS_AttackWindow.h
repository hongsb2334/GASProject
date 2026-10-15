// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_AttackWindow.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UANS_AttackWindow : public UAnimNotifyState
{
	GENERATED_BODY()

public:

    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
    void SetHitbox(USkeletalMeshComponent* MeshComp, bool bEnabled) const;

};
