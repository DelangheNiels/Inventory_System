// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemOptionButtons.h"
#include "InventorySlot.h"

#include "../Interfaces/Usable.h"

#include "../Character/ThirdPersonCharacter.h"

#include "../Items/InventoryItem.h"

#include "Components/Button.h"

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

	if (!m_pItem->GetClass()->ImplementsInterface(UUsable::StaticClass()))
	{
		m_pUseButton->SetIsEnabled(false);
	}
}

UInventorySlot* UItemOptionButtons::GetSlot() const
{
	return m_pSlot;
}

void UItemOptionButtons::SetSlot(UInventorySlot* invSlot)
{
	m_pSlot = invSlot;
}

void UItemOptionButtons::UseItem()
{
	if (m_pItem->GetClass()->ImplementsInterface(UUsable::StaticClass()) && m_pSlot)
	{
		m_pSlot->UseInventoryItem();
	}
}
