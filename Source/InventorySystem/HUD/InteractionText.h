// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionText.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInteractionText : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	void SetText(const FString& text);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* m_pTextBlock;

private:

	
	
};
