// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "NativeGameplayTags.h"

namespace LOPGameplayTags
{
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Attack);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Sprint);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Dodge);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_Ability_Guard);


    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Moving);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Attacking);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Dodging);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Guarding);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Sprinting);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_StaminaRegenBlocked);
    
    
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Dead);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Attack);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Attack_Hit);

    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_HitCheck);

    //콤보
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_ComboInput);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_ComboWindow_Open);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Character_ComboWindow_Close);



    //스태미너 상태
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina_State_Empty);
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stamina_State_Remain);


    


}