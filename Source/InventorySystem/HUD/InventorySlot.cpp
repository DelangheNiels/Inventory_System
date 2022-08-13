// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

#include "../Items/InventoryItem.h"

#include "../Components/InventoryComponent.h"

#include "../HUD/Inventory.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UInventorySlot::Initialize()
{
	bool success = Super::Initialize();

	return success;
}

UInventoryItem* UInventorySlot::GetItem() const
{
	return m_pItem;
}

void UInventorySlot::RemoveInventoryItem()
{
	auto inventoryWidget = m_pItem->GetOwningInventory()->GetInventoryWidget();
	m_pItem->GetOwningInventory()->RemoveItem(m_pItem);
	m_pItem = nullptr;
}

void UInventorySlot::SetItem(UInventoryItem* item)
{
	m_pItem = item;

	if (item)
	{
		m_pItemName->SetText(item->GetItemName());
		m_pButton->SetToolTipText(item->GetDescription());
		m_pButton->WidgetStyle.Normal.SetResourceObject(item->GetImage());
	}
}
