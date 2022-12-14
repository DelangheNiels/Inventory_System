// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;
class ATPCController;
class UInventoryItem;

UCLASS()
class INVENTORYSYSTEM_API AThirdPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AThirdPersonCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetHealth() const;
	void AddHealth(float health);

	bool AddItemToInventory(UInventoryItem* item, int amount = 1);

	ATPCController* GetPlayerController() const;

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
		float m_BaseTurnRate = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float m_BaseLookUpRate = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float m_BoomLength = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float m_BoomHeight = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float m_StartPitch = 10.0f;

	UPROPERTY()
		USpringArmComponent* m_pCameraBoom;

	UPROPERTY()
		UCameraComponent* m_pCamera;

	UPROPERTY()
		UInventoryComponent* m_pInventoryComponent;

	UPROPERTY()
		ATPCController* m_pController;

	float m_Health;

	void MoveForwardBackward(float value);
	void MoveLeftRight(float value);

	void TurningUsingControllerAtRate(float rate);
	void LookUpUsingControllerAtRate(float rate);

	void OpenCloseInventory();

	void Interact();

	FHitResult SingleLineTrace(const FVector& startLocation, const FVector& endLocation);

	float m_LineTraceLength;

};
