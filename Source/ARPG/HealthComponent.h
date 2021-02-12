// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthReachedZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthReachedZero OnHealthReachedZero;

	UFUNCTION(BlueprintCallable)
	float AddHealth(float Value);

	UFUNCTION(BlueprintCallable)
	float RemoveHealth(float Value);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleInstanceOnly)
	float CurrentHealth;

	UPROPERTY(VisibleInstanceOnly)
	bool bHealthReachedZero;

	float ModifyHealth(float Value);
};
