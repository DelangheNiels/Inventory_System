// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * 
 */

class UStaticMesh;
class UTexture2D;
class UInventoryComponent;

UCLASS(Abstract, Blueprintable, DefaultToInstanced, EditInlineNew)
class INVENTORYSYSTEM_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:

	UInventoryItem();

	UFUNCTION(BlueprintCallable)
		FText GetItemName() const;

	UFUNCTION(BlueprintCallable)
		FText GetDescription() const;

	UFUNCTION(BlueprintCallable)
		UStaticMesh* GetMesh() const;

	UFUNCTION(BlueprintCallable)
		UTexture2D* GetImage() const;

	UFUNCTION(BlueprintCallable)
		UInventoryComponent* GetOwningInventory() const;

	void SetOwningInventory(UInventoryComponent* inventory);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FText m_ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (Multiline = true)) //possible to have text on multiple lines
		FText m_ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		UStaticMesh* m_pMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		UTexture2D* m_pImage;

	//inventory where this item is located
	UPROPERTY()
		UInventoryComponent* m_pOwningInventroy;

private:

	
};
