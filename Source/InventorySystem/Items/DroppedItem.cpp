// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedItem.h"
#include "InventoryItem.h"

#include "../Character/ThirdPersonCharacter.h"

#include "Components/SphereComponent.h"

// Sets default values
ADroppedItem::ADroppedItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetupAttachment(RootComponent);

	

	
}

// Called when the game starts or when spawned
void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();
		
	SetMesh();
	
}

// Called every frame
void ADroppedItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADroppedItem::SetItemData(UInventoryItem* itemData)
{
	m_pItemData = itemData;

	SetMesh();
}

void ADroppedItem::Interact(AThirdPersonCharacter* player)
{	
	if (player->AddItemToInventory(m_pItemData))
	{
		Destroy();
	}
		
}

FString ADroppedItem::GetText() const
{
	return m_InteractionText;
}

void ADroppedItem::SetMesh()
{
	if (m_pItemData)
	{
		m_pMesh->SetStaticMesh(m_pItemData->GetMesh());
		m_pMesh->SetRelativeScale3D(FVector(4, 4, 4));
		m_pMesh->SetSimulatePhysics(true);
	}
}


