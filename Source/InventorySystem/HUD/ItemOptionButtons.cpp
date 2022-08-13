// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemOptionButtons.h"

#include "../Interfaces/Usable.h"

#include "../Character/ThirdPersonCharacter.h"

#include "../Items/InventoryItem.h"

bool UItemOptionButtons::Initialize()
{
	return Super::Initialize();
}

UInventoryItem* UItemOptionButtons::GetItem() const
{
	return m_pItem;
}

void UItemOptionButtons::SetItem(UInventoryItem* item)
{
	m_pItem = item;
}

void UItemOptionButtons::UseItem()
{
	if (m_pItem->GetClass()->ImplementsInterface(UUsable::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("has interface"));
	}
}
