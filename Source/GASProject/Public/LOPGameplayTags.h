// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "NativeGameplayTags.h"

namespace LOPGameplayTags
{
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Attack);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Attacking);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Dead);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Attack);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Attack_Hit);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_HitCheck);

}