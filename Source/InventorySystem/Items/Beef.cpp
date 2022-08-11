// Fill out your copyright notice in the Description page of Project Settings.


#include "Beef.h"

UBeef::UBeef()
{
	m_HealthToHeal = 20;
}

void UBeef::Use(AThirdPersonCharacter* player)
{
	player->AddHealth(m_HealthToHeal);
}
