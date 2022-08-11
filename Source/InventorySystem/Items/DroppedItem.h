// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroppedItem.generated.h"

class UStaticMeshComponent;
class UInventoryItem;
class USphereComponent;

UCLASS()
class INVENTORYSYSTEM_API ADroppedItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ADroppedItem();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	void SetItemData(UInventoryItem* itemData);


private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* m_pMesh;

	UPROPERTY(EditAnywhere)
		UInventoryItem* m_pItemData;

	UPROPERTY()
		USphereComponent* m_pSphereCollision;


	void SetMesh();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

};
