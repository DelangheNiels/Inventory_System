// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "../Items/InventoryItem.h"

#include "../HUD/InventorySlot.h"
#include "../HUD/Inventory.h"
#include "../HUD/ItemOptionButtons.h"

#include "Components/WidgetComponent.h"

#include "../Character/ThirdPersonCharacter.h"
#include "../Character/TPCController.h"

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

	auto controller = Cast<ATPCController>(GetWorld()->GetFirstPlayerController());
	auto player = Cast<AThirdPersonCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player)
	{
		m_pInventory = CreateWidget<UInventory, APlayerController>(controller, controller->GetInventoryWidget());

		if (m_pInventory)
		{
			m_pInventory->SetInventoryComp(this);
			m_pInventory->AddToViewport();
			m_pInventory->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
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
				m_pInventory->UpdateInventory();
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

		int index = m_Items.Find(item);
		m_Items[index] = nullptr;
		m_pInventory->UpdateInventory();
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

UInventory* UInventoryComponent::GetInventoryWidget() const
{
	return m_pInventory;
}

void UInventoryComponent::OpenCloseInventory(APlayerController* controller)
{
	if (m_pInventory->GetVisibility() == ESlateVisibility::Visible)
	{
		m_pInventory->SetVisibility(ESlateVisibility::Hidden);
		controller->SetInputMode(FInputModeGameOnly());
		controller->bShowMouseCursor = false;

		if (m_pInventory->GetActiveOptionWindow())
		{
			m_pInventory->GetActiveOptionWindow()->RemoveFromParent();
			m_pInventory->ClearActiveOptionWindow();
		}
	}

	else
	{
		m_pInventory->SetVisibility(ESlateVisibility::Visible);
		m_pInventory->UpdateInventory();
		controller->bShowMouseCursor = true;
		controller->SetInputMode(FInputModeGameAndUI());

	}
}

TArray<UInventoryItem*> UInventoryComponent::GetItems() const
{
	return m_Items;
}

