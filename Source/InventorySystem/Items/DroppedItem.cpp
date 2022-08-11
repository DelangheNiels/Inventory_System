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

	m_pSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	m_pSphereCollision->SetCollisionProfileName("Trigger");
	m_pSphereCollision->AttachToComponent(m_pMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_pSphereCollision->SetVisibility(true);
	m_pSphereCollision->SetHiddenInGame(false);

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_pMesh->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void ADroppedItem::BeginPlay()
{
	Super::BeginPlay();

	if (m_pSphereCollision)
	{
		m_pSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADroppedItem::OnOverlapBegin);
		m_pSphereCollision->SetRelativeScale3D(FVector(1, 1, 1));
	}
		
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

void ADroppedItem::SetMesh()
{
	if (m_pItemData)
	{
		m_pMesh->SetStaticMesh(m_pItemData->GetMesh());
		m_pMesh->SetRelativeScale3D(FVector(4, 4, 4));
		m_pMesh->SetSimulatePhysics(true);
	}
}

void ADroppedItem::OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor->IsA<AThirdPersonCharacter>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("test"));
	}
}

