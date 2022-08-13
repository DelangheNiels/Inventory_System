// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */

class UInventoryComponent;
class AThirdPersonCharacter;
class UInventorySlot;
class UItemOptionButtons;

UCLASS()
class INVENTORYSYSTEM_API UInventory : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	void SetInventoryComp(UInventoryComponent* inventoryComp);

	void UpdateInventory();

	UFUNCTION(BlueprintCallable)
		UItemOptionButtons* GetActiveOptionWindow() const;

	UFUNCTION(BlueprintCallable)
		void SetActiveOptionWindow(UItemOptionButtons* window);

	UFUNCTION(BlueprintCallable)
		void ClearActiveOptionWindow();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UWrapBox* m_pWrapBox;


private:

	UPROPERTY()
		UInventoryComponent* m_pInventoryComp;

	UPROPERTY()
		AThirdPersonCharacter* m_pPlayer;

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<UUserWidget> m_SlotWidget;

	UPROPERTY()
		UItemOptionButtons* m_pOptionWindow;

};
