// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAIController.h"

void APlayerAIController::Move(const FVector& Destination, float AcceptanceRadius)
{
	MoveToLocation(Destination, AcceptanceRadius, false);
}
