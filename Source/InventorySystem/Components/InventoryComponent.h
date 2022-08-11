// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
		bool AddItem(UInventoryItem* item, int amount = 1);

	UFUNCTION(BlueprintCallable)
		bool RemoveItem(UInventoryItem* item);

	UFUNCTION(BlueprintCallable)
		int GetCapacity() const;

	void SetCapacity(int capacity);

	UFUNCTION(BlueprintCallable)
		TArray<UInventoryItem*> GetItems() const;


private:

	UPROPERTY()
		TArray<UInventoryItem*> m_Items;

	int m_Capacity;

		
};
