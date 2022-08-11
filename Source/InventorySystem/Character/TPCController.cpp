// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCController.h"
#include "ThirdPersonCharacter.h"

#include "Components/WidgetComponent.h"

#include "../HUD/Inventory.h"

ATPCController::ATPCController(const FObjectInitializer& objectInitializer)
{
}

void ATPCController::BeginPlay()
{
	m_pPlayer = Cast<AThirdPersonCharacter>(GetPawn());

	if (m_pPlayer)
	{
		m_pInventory = CreateWidget<UInventory, APlayerController>(this, m_InventoryWidget);

		if (m_pInventory)
		{
			m_pPlayer->SetInventory(m_pInventory);
			m_pInventory->AddToViewport();
		}
	}
}
