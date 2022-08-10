// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPCController.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API ATPCController : public APlayerController
{
	GENERATED_BODY()

public:

	ATPCController(const FObjectInitializer& objectInitializer);
	
};
