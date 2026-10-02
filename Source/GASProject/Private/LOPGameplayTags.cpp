// Fill out your copyright notice in the Description page of Project Settings.


#include "LOPGameplayTags.h"

namespace LOPGameplayTags
{
    UE_DEFINE_GAMEPLAY_TAG(Character, "Character");
    UE_DEFINE_GAMEPLAY_TAG(Character_Ability, "Character.Ability");
    UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack, "Character_Ability_Attack");

    UE_DEFINE_GAMEPLAY_TAG(Character_State, "Character.State");
    UE_DEFINE_GAMEPLAY_TAG(Character_State_Attacking, "Character.State.Attacking");
    UE_DEFINE_GAMEPLAY_TAG(Character_State_Dead, "Character.State.Dead");

    UE_DEFINE_GAMEPLAY_TAG(Event, "Event");
    UE_DEFINE_GAMEPLAY_TAG(Event_Attack, "Event.Attack");
    UE_DEFINE_GAMEPLAY_TAG(Event_Attack_Hit, "Event.Attack.Hit");

    UE_DEFINE_GAMEPLAY_TAG(Event_Character, "Event.Character");
    UE_DEFINE_GAMEPLAY_TAG(Event_Character_HitCheck, "Event_Character_HitCheck");


}