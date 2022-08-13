// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "InventorySlot.h"

#include "../Components/InventoryComponent.h"

#include "Components/WrapBox.h"

bool UInventory::Initialize()
{
	bool success = Super::Initialize();
	UpdateInventory();
	return success;
}

void UInventory::SetInventoryComp(UInventoryComponent* inventoryComp)
{
	m_pInventoryComp = inventoryComp;
	UpdateInventory();
}

void UInventory::UpdateInventory()
{
	if (m_pInventoryComp && m_pWrapBox)
	{
		m_pWrapBox->ClearChildren();

		for (size_t i = 0; i < m_pInventoryComp->GetItems().Num(); i++)
		{
			auto slot = CreateWidget<UInventorySlot, APlayerController>(GetOwningPlayer(), m_SlotWidget);
			slot->SetItem(m_pInventoryComp->GetItems()[i]);

			m_pWrapBox->AddChild(slot);
		}
	}
}

UItemOptionButtons* UInventory::GetActiveOptionWindow() const
{
	return m_pOptionWindow;
}

void UInventory::SetActiveOptionWindow(UItemOptionButtons* window)
{
	m_pOptionWindow = window;
}

void UInventory::ClearActiveOptionWindow()
{
	m_pOptionWindow = nullptr;
}

