// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionText.h"

#include "Components/TextBlock.h"

bool UInteractionText::Initialize()
{
	return Super::Initialize();
}

void UInteractionText::SetText(const FString& text)
{
	m_pTextBlock->SetText(FText::FromString(text));
}
