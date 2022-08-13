// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemOptionButtons.generated.h"

/**
 * 
 */

class UInventoryItem;
class UInventorySlot;

UCLASS()
class INVENTORYSYSTEM_API UItemOptionButtons : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual bool Initialize() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* m_pDropButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* m_pUseButton;

	UFUNCTION(BlueprintCallable)
		UInventoryItem* GetItem() const;

	UFUNCTION(BlueprintCallable)
		void SetItem(UInventoryItem* item);

	UFUNCTION(BlueprintCallable)
		UInventorySlot* GetSlot() const;

	UFUNCTION(BlueprintCallable)
		void SetSlot(UInventorySlot* invSlot);

	UFUNCTION(BlueprintCallable)
		void UseItem();

private:

	UPROPERTY()
		UInventoryItem* m_pItem;

	UPROPERTY()
		UInventorySlot* m_pSlot;
	
};
