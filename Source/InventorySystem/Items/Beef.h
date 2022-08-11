// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "../Interfaces/Usable.h"
#include "Beef.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UBeef : public UInventoryItem, public IUsable
{
	GENERATED_BODY()

public:

	UBeef();

	virtual void Use(AThirdPersonCharacter* player) override;

private:

	float m_HealthToHeal;
	
};
