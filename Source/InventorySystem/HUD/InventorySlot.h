// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */

class UInventoryItem;
class ADroppedActor;
class UInventory;

UCLASS()
class INVENTORYSYSTEM_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* m_pItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* m_pButton;

	UFUNCTION(BlueprintCallable)
		UInventoryItem* GetItem() const;

	UFUNCTION(BlueprintCallable)
		void DropInventoryItem();

	UFUNCTION(BlueprintCallable)
		void UseInventoryItem();

	UFUNCTION(BlueprintCallable)
		UInventory* GetInventoryWidget() const;

	void SetItem(UInventoryItem* item);

private:

	UPROPERTY()
		UInventoryItem* m_pItem;

	float m_ItemDropDistance;
};
