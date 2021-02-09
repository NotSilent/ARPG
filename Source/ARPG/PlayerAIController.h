// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API APlayerAIController : public AAIController
{
	GENERATED_BODY()

public:
	void Move(const FVector& Destination, float AcceptanceRadius);
};
