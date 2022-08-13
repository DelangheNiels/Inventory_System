// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCController.h"
#include "ThirdPersonCharacter.h"

#include "Components/WidgetComponent.h"

#include "../HUD/Inventory.h"
#include "../HUD/InteractionText.h"

ATPCController::ATPCController(const FObjectInitializer& objectInitializer)
{
}

TSubclassOf<UUserWidget> ATPCController::GetInventoryWidget() const
{
	return m_InventoryWidget;
}

UInteractionText* ATPCController::GetInteractionTextWidget() const
{
	return m_pInteractionText;
}

void ATPCController::BeginPlay()
{
	m_pPlayer = Cast<AThirdPersonCharacter>(GetPawn());

	if (m_pPlayer)
	{
		m_pInteractionText = CreateWidget<UInteractionText, APlayerController>(this, m_InteractionTextWidget);

		if (m_pInteractionText)
		{
			m_pInteractionText->AddToViewport();
		}
	}
}
