// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{

}

FText UInventoryItem::GetItemName() const
{
	return m_ItemName;
}

FText UInventoryItem::GetDescription() const
{
	return m_ItemDescription;
}

UStaticMesh* UInventoryItem::GetMesh() const
{
	return m_pMesh;
}

UTexture2D* UInventoryItem::GetImage() const
{
	return m_pImage;
}

UInventoryComponent* UInventoryItem::GetOwningInventory() const
{
	return m_pOwningInventroy;
}

void UInventoryItem::SetOwningInventory(UInventoryComponent* inventory)
{
	m_pOwningInventroy = inventory;
}
