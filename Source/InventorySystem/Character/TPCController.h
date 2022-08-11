// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPCController.generated.h"

/**
 * 
 */

class AThirdPersonCharacter;
class UInventory;

UCLASS()
class INVENTORYSYSTEM_API ATPCController : public APlayerController
{
	GENERATED_BODY()

public:

	ATPCController(const FObjectInitializer& objectInitializer);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
		AThirdPersonCharacter* m_pPlayer;

	UPROPERTY()
		UInventory* m_pInventory;

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<UUserWidget> m_InventoryWidget;
	
};
