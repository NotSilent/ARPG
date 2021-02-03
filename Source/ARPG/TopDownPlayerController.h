// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public :
	virtual void SetupInputComponent() override;

private:
	void OnLeftMouseButtonClicked();
};
