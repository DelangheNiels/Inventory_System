// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interfaces/Interactable.h"
#include "../Interfaces/ShowText.h"

#include "DroppedItem.generated.h"

class UStaticMeshComponent;
class UInventoryItem;
class USphereComponent;

UCLASS()
class INVENTORYSYSTEM_API ADroppedItem : public AActor, public IInteractable, public IShowText
{
	GENERATED_BODY()
	
public:	
	
	ADroppedItem();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	void SetItemData(UInventoryItem* itemData);

	virtual void Interact(AThirdPersonCharacter* player) override;

	virtual FString GetText() const override;

	void SetText(FString text);


private:

		UStaticMeshComponent* m_pMesh;

	UPROPERTY(EditAnywhere)
		UInventoryItem* m_pItemData;

	UPROPERTY(EditAnywhere)
		FString m_InteractionText;

	void SetMesh();


};
