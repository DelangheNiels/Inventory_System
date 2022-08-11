// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

#include "../Items/InventoryItem.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UInventorySlot::Initialize()
{
	bool success = Super::Initialize();

	return success;
}

void UInventorySlot::SetItem(UInventoryItem* item)
{
	if (item)
	{
		//m_pItemImage->SetOpacity(1);
		m_pItemName->SetText(item->GetItemName());
		//m_pItemImage->SetBrushFromTexture(item->GetImage());
		m_pButton->SetToolTipText(item->GetDescription());
		m_pButton->WidgetStyle.Normal.SetResourceObject(item->GetImage());
	}
}