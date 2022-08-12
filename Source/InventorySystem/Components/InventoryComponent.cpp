// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "../Items/InventoryItem.h"

#include "../HUD/InventorySlot.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//Fill inventory with empty items
	m_Capacity = 20;
	m_Items.SetNum(m_Capacity);
}



void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UInventoryComponent::AddItem(UInventoryItem* item, int amount)
{
	if (item)
	{
		for (size_t i = 0; i < m_Items.Num(); i++)
		{
			if (!m_Items[i])
			{
				m_Items[i] = item;
				m_Items[i]->SetOwningInventory(this);
				return true;

			}
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItem(UInventoryItem* item)
{
	if (m_Items.Contains(item))
	{
		item->SetOwningInventory(nullptr);
		m_Items.Remove(item);
		return true;
	}
	return false;
}

int UInventoryComponent::GetCapacity() const
{
	return m_Capacity;
}

void UInventoryComponent::SetCapacity(int capacity)
{
	m_Capacity = capacity;
	m_Items.SetNum(m_Capacity);
}

TArray<UInventoryItem*> UInventoryComponent::GetItems() const
{
	return m_Items;
}

