// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

#include "../Items/InventoryItem.h"
#include "../Items/DroppedItem.h"

#include "../Components/InventoryComponent.h"

#include "../HUD/Inventory.h"

#include "../Interfaces/Usable.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UInventorySlot::Initialize()
{
	bool success = Super::Initialize();

	m_ItemDropDistance = 70.0f;

	return success;
}

UInventoryItem* UInventorySlot::GetItem() const
{
	return m_pItem;
}

void UInventorySlot::DropInventoryItem()
{
	//Drop item
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto droppedItem = GetWorld()->SpawnActor<ADroppedItem>(player->GetActorLocation() + player->GetActorForwardVector() * m_ItemDropDistance, player->GetActorRotation());
	droppedItem->SetItemData(m_pItem);
	droppedItem->SetText("Press E to pick up");

	//Remove item from inventory
	auto inventoryWidget = m_pItem->GetOwningInventory()->GetInventoryWidget();
	m_pItem->GetOwningInventory()->RemoveItem(m_pItem);
	m_pItem = nullptr;
}

void UInventorySlot::UseInventoryItem()
{
	if (m_pItem->GetClass()->ImplementsInterface(UUsable::StaticClass()))
	{
		IUsable* usableInterface = Cast<IUsable>(m_pItem);
		auto player = Cast<AThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		usableInterface->Use(player);

		auto inventoryWidget = m_pItem->GetOwningInventory()->GetInventoryWidget();
		m_pItem->GetOwningInventory()->RemoveItem(m_pItem);
		m_pItem = nullptr;
	}

}

UInventory* UInventorySlot::GetInventoryWidget() const
{
	return m_pItem->GetOwningInventory()->GetInventoryWidget();
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
