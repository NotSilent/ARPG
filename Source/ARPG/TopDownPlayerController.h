// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerAIController.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "PlayerHUD.h"

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

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	void MovePlayerToMousePosition();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerCharacter> PlayerCharacterClass;

	UPROPERTY(VisibleInstanceOnly)
	APlayerAIController* PlayerAIController;

	UPROPERTY(VisibleInstanceOnly)
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerHUD> PlayerWidgetClass;

	UPROPERTY(VisibleInstanceOnly)
	UPlayerHUD* PlayerWidget;

	UFUNCTION()
	void OnLeftMouseButtonPressed();

	UFUNCTION()
	void OnLeftMouseButtonReleased();

	UFUNCTION()
	void OnRightMouseButtonClicked();

	UFUNCTION()
	void OnPlayerHealthChanged(float PercentValue, float Value);

	bool bLMBDown;
};
