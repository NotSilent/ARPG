// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerAIController.generated.h"

class APlayerCharacter;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class ARPG_API APlayerAIController : public AAIController
{
	GENERATED_BODY()

public:
	void Move(const FVector& Destination);

	void InitSpell(const FVector& Destination);

	UFUNCTION(BlueprintCallable)
	void StartCastingSpell();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviourTree;

	UPROPERTY(VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* PlayerCharacter;

	UFUNCTION()
	void OnPlayerStoppedCasting();
};
