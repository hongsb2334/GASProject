// Fill out your copyright notice in the Description page of Project Settings.


#include "LOPGameplayTags.h"

namespace LOPGameplayTags
{
    UE_DEFINE_GAMEPLAY_TAG(Character, "Character");
    UE_DEFINE_GAMEPLAY_TAG(Character_Ability, "Character.Ability");
    UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack, "Character.Ability.Attack");
    UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Dodge, "Character.Ability.Dodge");
    UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Guard, "Character.Ability.Guard");



    UE_DEFINE_GAMEPLAY_TAG(Character_State, "Character.State");
    UE_DEFINE_GAMEPLAY_TAG(Character_State_Attacking, "Character.State.Attacking");
    UE_DEFINE_GAMEPLAY_TAG(Character_State_StaminaRegenBlocked, "Character.State.StaminaRegenBlocked");

    UE_DEFINE_GAMEPLAY_TAG(Character_State_Dodging, "Character.State.Dodging");
    UE_DEFINE_GAMEPLAY_TAG(Character_State_Guarding, "Character.State.Guarding");
    
    
    UE_DEFINE_GAMEPLAY_TAG(Character_State_Dead, "Character.State.Dead");

    UE_DEFINE_GAMEPLAY_TAG(Event, "Event");
    UE_DEFINE_GAMEPLAY_TAG(Event_Attack, "Event.Attack");
    UE_DEFINE_GAMEPLAY_TAG(Event_Attack_Hit, "Event.Attack.Hit");

    UE_DEFINE_GAMEPLAY_TAG(Event_Character, "Event.Character");
    UE_DEFINE_GAMEPLAY_TAG(Event_Character_HitCheck, "Event.Character.HitCheck");

    UE_DEFINE_GAMEPLAY_TAG(Event_Character_ComboInput, "Event.Character.CompoInput");
    UE_DEFINE_GAMEPLAY_TAG(Event_Character_ComboWindow_Open, "Event.Character.ComboWindow.Open");
    UE_DEFINE_GAMEPLAY_TAG(Event_Character_ComboWindow_Close, "Event.Character.ComboWindow.Close");

    UE_DEFINE_GAMEPLAY_TAG(Stamina_State_Empty, "Stamina.State.Empty");
    UE_DEFINE_GAMEPLAY_TAG(Stamina_State_Remain, "Stamina.State.Remain");
}