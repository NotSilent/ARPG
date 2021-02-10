// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerAIController.h"
#include "PlayerCharacter.h"
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
	ATopDownPlayerController();

	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerCharacter> PlayerCharacterClass;

	UPROPERTY(VisibleInstanceOnly)
	APlayerAIController* PlayerAIController;

	UPROPERTY(VisibleInstanceOnly)
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float AcceptanceRadius;

	UFUNCTION()
	void OnLeftMouseButtonClicked();

	UFUNCTION()
	void OnRightMouseButtonClicked();
};
